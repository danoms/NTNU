

void wait_ms(uint32_t ms);
void wait_us(uint32_t us);
void dummy_clock(int cycles);
void manual_clock(int cycles);
uint8_t send_cmd(uint8_t cmd, uint32_t arg);
void manual_send(uint8_t data);
uint8_t manual_read();
void power_sequence(void);
uint8_t test_bench();
void power_sequence(void);