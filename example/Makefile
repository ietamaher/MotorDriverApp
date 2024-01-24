CC=g++
CFLAGS=-I/home/rapit/Fast-DDS/install/fastrtps/include -I/usr/include/modbus
LDFLAGS=-L/home/rapit/Fast-DDS/install/fastrtps/lib   -lfastcdr -lfastrtps -lmodbus

MotorDriverApp: main.cpp ResponsePublisher.cpp StatePublisher.cpp QuerySubscriber.cpp
	$(CC) $(CFLAGS) -o MotorDriverApp main.cpp ResponsePublisher.cpp StatePublisher.cpp QuerySubscriber.cpp $(LDFLAGS)

clean:
	rm MotorDriverApp
