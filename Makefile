compile:
	arduino-cli compile --fqbn stm32duino:STM32F1:genericSTM32F103C "${HOME}/Arduino/stm32-remote-control-car"

upload:
	arduino-cli upload -p /dev/ttyACM0 --fqbn stm32duino:STM32F1:genericSTM32F103C "${HOME}/Arduino/stm32-remote-control-car"