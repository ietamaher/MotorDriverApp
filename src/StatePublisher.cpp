#include "State_msgPubSubTypes.h"

#include <chrono>
#include <thread>

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>
#include "State_msg.h"  // Include the generated header for State_msg

using namespace eprosima::fastdds::dds;

class StatePublisher {
private:
    DomainParticipant* participant_;
    Publisher* publisher_;
    Topic* topic_;
    DataWriter* writer_;
    TypeSupport type_;

public:
    StatePublisher() : participant_(nullptr), publisher_(nullptr), topic_(nullptr), writer_(nullptr), type_(new State_msgPubSubType()) {}

    virtual ~StatePublisher() {
        if (writer_) {
            publisher_->delete_datawriter(writer_);
        }
        if (publisher_) {
            participant_->delete_publisher(publisher_);
        }
        if (topic_) {
            participant_->delete_topic(topic_);
        }
        DomainParticipantFactory::get_instance()->delete_participant(participant_);
    }

    bool init() {
        // Create and initialize domain participant
        DomainParticipantQos participantQos;
        participantQos.name("StatePublisher");
        participant_ = DomainParticipantFactory::get_instance()->create_participant(0, participantQos);
        if (participant_ == nullptr) {
            return false;
        }

        // Register the Type
        type_.register_type(participant_);

        // Create the Topic
        topic_ = participant_->create_topic("AZD_State", "State_msg", TOPIC_QOS_DEFAULT);
        if (topic_ == nullptr) {
            return false;
        }

        // Create the Publisher
        publisher_ = participant_->create_publisher(PUBLISHER_QOS_DEFAULT, nullptr);
        if (publisher_ == nullptr) {
            return false;
        }

        // Create the DataWriter
        writer_ = publisher_->create_datawriter(topic_, DATAWRITER_QOS_DEFAULT, nullptr);
        if (writer_ == nullptr) {
            return false;
        }

        return true;
    }

    void publish(State_msg& msg) {
        writer_->write(&msg);
    }
};
