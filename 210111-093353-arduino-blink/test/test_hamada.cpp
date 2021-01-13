#include <Arduino.h>
#include <unity.h>
#include "Common.h"
#include "Master.h"
#include "Master_CBK.h"
#include "stub.h"

void Test_1()
{
    Master_CurrentServiceID = SLAVE_MODE_SET;
    Master_UnactivateService();
    TEST_ASSERT_EQUAL(NOT_ACTIVE, Master_CurrentServiceID);
    TEST_PASS_MESSAGE("UN activate is working very well");
}

void Test_2()
{
    Master_CurrentServiceID = NOT_ACTIVE;
    Master_HandlerServices_CBK('#');
    Master_HandlerServices_CBK('1');
    TEST_ASSERT_EQUAL(SLAVE_MODE_SET, Master_CurrentServiceID);
    TEST_PASS_MESSAGE("Enter mode is working very well");
}



void Test_4()
{
    Master_CurrentServiceID = NOT_ACTIVE;
    TEST_ASSERT_EQUAL_MESSAGE(GET_SLAVE_ID, SetSlaveModeSubSrvID, "Getting Slave Id");
    TEST_PASS_MESSAGE("Getting Slave Id");

    Master_HandlerServices_CBK('#');
    Master_HandlerServices_CBK('1');
    Master_HandlerServices_CBK('7');
    Master_HandlerServices_CBK('#');
    TEST_ASSERT_EQUAL_MESSAGE(7, (SlaveModeInfo.Salve_ID),"Slave ID True");
    TEST_PASS_MESSAGE("Slave ID True");

    TEST_ASSERT_EQUAL_MESSAGE(GET_TIME_MIN, SetSlaveModeSubSrvID, "Getting Time in mins");
    TEST_PASS_MESSAGE("Getting Time in mins");

    Master_HandlerServices_CBK('1');
    Master_HandlerServices_CBK('2');
    Master_HandlerServices_CBK('0');
    Master_HandlerServices_CBK('#');
    TEST_ASSERT_EQUAL_MESSAGE(GET_COUNT_TYPE, SetSlaveModeSubSrvID, "Getting Count Style");
    TEST_PASS_MESSAGE("Getting Count Style");
    TEST_ASSERT_EQUAL(120, SlaveModeInfo.Time_mins);
}

void setup()
{
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    delay(1000);
    Serial.begin(9600);
    UNITY_BEGIN(); // IMPORTANT LINE!
}

void loop()
{

    RUN_TEST(Test_1);
    RUN_TEST(Test_2);
    RUN_TEST(Test_4);

    UNITY_END(); // stop unit testing
}
