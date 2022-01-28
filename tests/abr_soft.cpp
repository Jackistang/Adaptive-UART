#include "abr.h"
#include "CppUTest/TestHarness.h"
#include "CppUTest/CommandLineTestRunner.h"

#define ARRAY_SIZE(array)   (sizeof(array) / sizeof(array[0]))

static uint8_t g_timestamps_idx = 0;
static uint64_t g_timestamps[] = {
    0, 69, 115942,
    0, 833, 9603,
};
static void (*g_test_irq_handler)(void);

uint64_t abr_soft_get_timestamp(void)
{
    return g_timestamps[g_timestamps_idx++];
}

void abr_soft_pin_irq_rising(void (*irq_handler)(void))
{
    g_test_irq_handler = irq_handler;
}

TEST_GROUP(AbrSoftTestGroup)
{
	void setup()
   {
      g_timestamps_idx = 0;
      abr_init();
   }

   void teardown()
   {
      // Un-init stuff
   }
};

TEST(AbrSoftTestGroup, abrSoftSuccess)
{
    while (g_timestamps_idx < ARRAY_SIZE(g_timestamps)) {
        /* 触发两次 */
        g_test_irq_handler();
        g_test_irq_handler();

        uint32_t baudrate = abr_get_baudrate();
        CHECK_EQUAL(g_timestamps[g_timestamps_idx++], baudrate);
    }
}

IGNORE_TEST(AbrSoftTestGroup, abrSoftFail)
{
    g_test_irq_handler();
    uint32_t baudrate = abr_get_baudrate();
    CHECK_EQUAL(0, baudrate);
}


int main(int ac, char** av)
{
    return CommandLineTestRunner::RunAllTests(ac, av);
}