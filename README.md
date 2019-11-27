# A delay switch example sketch for ATtiny13A

1. Sleep until external interrupt PB1 (INT0)
2. After 'DELAY_MSEC' milliseconds, set 'OUTPUT_PIN' to HIGH for 'TIMES' times and 'DURATION_MSEC' milliseconds.
3. Sleep again.

![example circuit](https://raw.githubusercontent.com/sgr/attiny13a_delay_switch/master/example_circuit.png)

## Prerequisites

- Arduino IDE
- bitDuino13

See [Arduino IDE に ATtiny10/13 の開発環境を組み込む](https://make.kosakalab.com/make/electronic-work/arduino-ide/attiny10-13_dev/).

## License
MIT