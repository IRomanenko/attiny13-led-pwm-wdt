
void initializeTimer0PWM(void) {
    TCCR0A = (1 << COM0A1) | (1 << COM0B1) | (1 << COM0B0) | (1 << WGM00);
    OCR0A  = 75;
    TCNT0  = 0x00;
}

void deInitializeTimer0PWM(void) {
    TCCR0A = 0x00;
    OCR0A  = 0x00;
    TCNT0  = 0x00;
}

void startTimer0PWM(void) {
    TCCR0B |= (1 << CS01);
}

void stopTimer0PWM(void) {
    TCCR0B = (0 << CS01);
    TCNT0  = 0x00;
}

void setTimer0PWMOutput(unsigned char width) {
    TCNT0 = 0x00;
    OCR0A = width;
}
