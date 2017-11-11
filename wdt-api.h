
void initWDT(void) {
    wdt_enable(WDTO_500MS);
    WDTCR |= _BV(WDTIE);
    set_sleep_mode(SLEEP_MODE_IDLE);
}
