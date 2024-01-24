#include "Query_msgPubSubTypes.h"

#include <chrono>
#include <thread>

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>
#include <fastdds/dds/subscriber/SampleInfo.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>
//#include "Query_msg.h"  // Include the generated header for Query_msg
#include <modbus/modbus.h>


using namespace eprosima::fastdds::dds;

class QuerySubscriber {
private:
    DomainParticipant* participant_;
    Subscriber* subscriber_;
    Topic* topic_;
    DataReader* reader_;
    TypeSupport type_;

    class SubListener : public DataReaderListener {
    public:
        SubListener() : samples_(0) {}

        void on_subscription_matched(DataReader*, const SubscriptionMatchedStatus& info) override {
            if (info.current_count_change == 1) {
                std::cout << "Subscriber matched." << std::endl;
            } else if (info.current_count_change == -1) {
                std::cout << "Subscriber unmatched." << std::endl;
            }
        }

        void on_data_available(DataReader* reader) override {
            SampleInfo info;
            Query_msg query_msg;
            if (reader->take_next_sample(&query_msg, &info) == ReturnCode_t::RETCODE_OK) {
                if (info.valid_data) {
                    // Example: Print received query information
                    std::cout << "Received Query: Slave ID: " << (int)query_msg.slave_id() << ", Func Code: " << (int)query_msg.func_code()  << ", Write Add : " << (int)query_msg.write_addr() << std::endl;
                    // Handle the query based on func_code
                    if (query_msg.func_code() == 1) { // Example func_code for write
                        // Call Modbus write function
                        modbus_write_function(query_msg.slave_id(), query_msg.write_addr(), query_msg.write_num(), query_msg.data());
                    } else if (query_msg.func_code() == 2) { // Example func_code for read
                        // Call Modbus read function
                        modbus_read_function(query_msg.slave_id(), query_msg.read_addr(), query_msg.read_num());
                    }
 
                    // Handle other func_codes as needed

                    samples_++;
                }
            }
        }

         void modbus_write_function(int8_t slave_id, int32_t write_addr, int8_t write_num, const std::array<unsigned int, 64>& data){
            modbus_t *ctx;
            ctx = modbus_new_rtu("/dev/pts/6", 19200, 'N', 8, 1);
            modbus_set_slave(ctx, slave_id);

            if (ctx == NULL) {
                fprintf(stderr, "Unable to create the libmodbus context\n");
               // return -1;
            }

            if (modbus_connect(ctx) == -1) {
                fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
                modbus_free(ctx);
                //return -1;
            } 

            // Convert data to the format suitable for Modbus (e.g., split into int16)
            uint16_t modbus_data[128]; // Since we are splitting each int32 into two int16
            for (int i = 0, j = 0; i < write_num; i++, j += 2) {
                modbus_data[j] = (data[i] >> 16) & 0xFFFF;   // High word
                modbus_data[j + 1] = data[i] & 0xFFFF;       // Low word
            }

            // Write data to Modbus
            int rc = modbus_write_registers(ctx, write_addr, write_num * 2, modbus_data);
 
            //int modbus_write_registers(modbus_t *ctx, int addr, int nb, const uint16_t *src);

            if (rc == -1) {
                fprintf(stderr, "Modbus write failed: %s\n", modbus_strerror(errno));
            }

            modbus_close(ctx);
            modbus_free(ctx);
        }

        void modbus_read_function(int8_t slave_id, int32_t read_addr, int8_t read_num) {
            modbus_t *ctx;
            ctx = modbus_new_rtu("/dev/pts/6", 19200, 'N', 8, 1);
            modbus_set_slave(ctx, slave_id);

            if (modbus_connect(ctx) == -1) {
                fprintf(stderr, "Connection failed: %s\n", modbus_strerror(errno));
                modbus_free(ctx);
                return;
            }

            uint16_t modbus_data[128]; // Adjust size based on the maximum expected read_num
            int rc = modbus_read_registers(ctx, read_addr, read_num * 2, modbus_data);
            if (rc == -1) {
                fprintf(stderr, "Modbus read failed: %s\n", modbus_strerror(errno));
            } else {
                // Process the received data
                for (int i = 0; i < rc; i += 2) {
                    int32_t value = (modbus_data[i] << 16) | modbus_data[i + 1];
                    // Handle or store the value as needed
                    // Example: printf("Read value: %d\n", value);
                }
            }

            modbus_close(ctx);
            modbus_free(ctx);
        }





        std::atomic_int samples_;
    } listener_;

public:
    QuerySubscriber() : participant_(nullptr), subscriber_(nullptr), topic_(nullptr), reader_(nullptr), type_(new Query_msgPubSubType()) {}

    virtual ~QuerySubscriber() {
        if (reader_) {
            subscriber_->delete_datareader(reader_);
        }
        if (topic_) {
            participant_->delete_topic(topic_);
        }
        if (subscriber_) {
            participant_->delete_subscriber(subscriber_);
        }
        DomainParticipantFactory::get_instance()->delete_participant(participant_);
    }

    bool init() {
        DomainParticipantQos participantQos;
        participantQos.name("QuerySubscriber");
        participant_ = DomainParticipantFactory::get_instance()->create_participant(0, participantQos);

        if (participant_ == nullptr) {
            return false;
        }

        type_.register_type(participant_);

        topic_ = participant_->create_topic("AZD_query", "Query_msg", TOPIC_QOS_DEFAULT);
        if (topic_ == nullptr) {
            return false;
        }

        subscriber_ = participant_->create_subscriber(SUBSCRIBER_QOS_DEFAULT, nullptr);
        if (subscriber_ == nullptr) {
            return false;
        }

        reader_ = subscriber_->create_datareader(topic_, DATAREADER_QOS_DEFAULT, &listener_);
        if (reader_ == nullptr) {
            return false;
        }

        return true;
    }

    void run(uint32_t samples) {
        while(listener_.samples_ < samples) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
};
