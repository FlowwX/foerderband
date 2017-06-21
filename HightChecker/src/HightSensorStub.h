#ifndef HIGHT_SENSOR_STUB_
#define HIGHT_SENSOR_STUB_

#define INIT_SIZE 1000

#define SENSOR_FILE_1 "C:/Users/flori/workspace/HightChecker/logs/processlog1.txt"
#define SENSOR_FILE_2 "C:/Users/flori/workspace/HightChecker/logs/processlog2.txt"
#define SENSOR_FILE_3 "C:/Users/flori/workspace/HightChecker/logs/processlog3.txt"

class HightSensorStub {

private:
	int *values;
	int index;
    int size;

public:
    HightSensorStub(void);
	int nextValue();
	int getSize();

	void readValuesFromFile(const char* path);
};

#endif //HIGHT_SENSOR_STUB_
