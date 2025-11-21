<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>STM32 Bare-Metal Drivers</title>
</head>
<body>

<h1>STM32 Drivers Repository</h1>

<h3>Overview</h3>
<p>
This repository contains a collection of <strong> drivers for STM32 microcontrollers</strong>, written using direct register-level programming without HAL or LL libraries. 
The main goal is to help students and embedded developers understand STM32 peripherals internally, while providing reusable and scalable modules for real firmware projects.
</p>

<h3>Main Features</h3>
<ul>
    <li>Pure register-level implementation (no HAL, no LL)</li>
    <li>Individual driver modules for easy reuse</li>
    <li>Readable and clean code suitable for learning and teaching</li>
    <li>Includes peripherals such as GPIO, EXTI, NVIC, UART, ADC, DMA, RCC, SysTick, and advanced timers</li>
</ul>

<hr>

<h2>Repository Structure</h2>
<pre>
STM32_Modules/
│
├── ADC_V1
├── DMA_V1
├── EXTI_V1
├── GPIO_V1_
├── NVIC_V1
├── RCC_V1_
├── STK_V1_
├── TIM1_8_V1
├── UART1_V1_
│
└── baremetal/
</pre>

<p>
Each module directory includes:
</p>

<ul>
    <li><strong>.c / .h files</strong> implementing the driver</li>
    <li><strong>Configuration files</strong> (if needed)</li>
    <li>Example usage code</li>
</ul>

<hr>

<h2>Modules Description</h2>

<h3>1️⃣ RCC – Reset & Clock Control</h3>
<p><strong>Folder:</strong> RCC_V1_</p>
<p>Handles clock system configuration and peripheral clock enabling.</p>
<ul>
    <li>Enable/disable peripheral clocks</li>
    <li>Select system clock source (HSI / HSE / PLL)</li>
    <li>Control AHB/APB bus prescalers</li>
</ul>

<hr>

<h3>2️⃣ GPIO – General-Purpose Input/Output</h3>
<p><strong>Folder:</strong> GPIO_V1_</p>
<p>Handles STM32 digital I/O pin configuration and operation.</p>
<ul>
    <li>Set pin mode (input, output, AF, analog)</li>
    <li>Configure pull-up / pull-down</li>
    <li>Select push/pull or open-drain output</li>
    <li>Read and write digital values</li>
</ul>

<hr>

<h3>3️⃣ NVIC – Nested Vectored Interrupt Controller</h3>
<p><strong>Folder:</strong> NVIC_V1</p>
<p>Controls interrupt enabling, disabling, and priority assignments.</p>
<ul>
    <li>Enable/disable specific interrupts</li>
    <li>Set priority levels</li>
    <li>Software interrupt triggering</li>
</ul>

<hr>

<h3>4️⃣ EXTI – External Interrupts</h3>
<p><strong>Folder:</strong> EXTI_V1</p>
<p>Handles interrupt events coming from external pins.</p>
<ul>
    <li>Select EXTI line input source</li>
    <li>Choose trigger type (rising, falling, both)</li>
    <li>Register callback handlers</li>
    <li>Clear interrupt flags</li>
</ul>

<hr>

<h3>5️⃣ SysTick Timer</h3>
<p><strong>Folder:</strong> STK_V1_</p>
<p>System tick timer driver used for time delays and periodic interrupts.</p>
<ul>
    <li>Millisecond and microsecond delays</li>
    <li>Callback-based periodic interrupts</li>
    <li>System tick counters</li>
</ul>

<hr>

<h3>6️⃣ TIM1 & TIM8 – Advanced Timers</h3>
<p><strong>Folder:</strong> TIM1_8_V1</p>
<p>Advanced timing and PWM driver for motor control and precise timing applications.</p>
<ul>
    <li>Configure timer prescalers and auto-reload values</li>
    <li>Generate PWM output on multiple channels</li>
    <li>Interrupt-based event handling</li>
</ul>

<hr>

<h3>7️⃣ DMA – Direct Memory Access</h3>
<p><strong>Folder:</strong> DMA_V1</p>
<p>Enables memory and peripheral data transfers without CPU load.</p>
<ul>
    <li>Memory-to-peripheral and peripheral-to-memory transfer</li>
    <li>Circular and normal transfer modes</li>
    <li>Half and full transfer complete interrupts</li>
    <li>Configurable data size and priority</li>
</ul>

<hr>

<h3>8️⃣ ADC – Analog-to-Digital Converter</h3>
<p><strong>Folder:</strong> ADC_V1</p>
<p>Measures analog voltages from sensors and converts them to digital values.</p>
<ul>
    <li>Single and multi-channel sampling</li>
    <li>Software and trigger-based conversion</li>
    <li>DMA data handling</li>
    <li>Raw result register reading</li>
</ul>

<hr>

<h3>9️⃣ UART1 – Serial Communication</h3>
<p><strong>Folder:</strong> UART1_V1_</p>
<p>Provides standard asynchronous serial communication.</p>
<ul>
    <li>Supports polling or interrupt-based communication</li>
    <li>Baud rate configuration</li>
    <li>Transmits strings, single bytes, and buffers</li>
    <li>Callback support for received data</li>
</ul>

<hr>

<h2>Building & Requirements</h2>
<p>You can use any STM32 development environment, such as:</p>
<ul>
    <li>STM32CubeIDE</li>
    <li>Keil uVision</li>
    <li>IAR Embedded Workbench</li>
    <li>GCC / Makefile projects</li>
</ul>

<p>Programmers supported:</p>
<ul>
    <li>ST-Link</li>
    <li>J-Link</li>
    <li>Any SWD-compatible debugger</li>
</ul>

<hr>

<h2>Development Philosophy</h2>
<ul>
    <li>Drivers are <strong>independent and reusable</strong></li>
    <li>No HAL or CMSIS needed</li>
    <li>Ideal for teaching embedded fundamentals</li>
    <li>Intended for interview preparation and hands-on understanding</li>
</ul>

<hr>

<h2>Contributions</h2>
<p>
Contributions, suggestions, and feature additions are welcome. You may:
</p>
<ul>
    <li>Submit pull requests</li>
    <li>Report issues</li>
    <li>Request new modules or enhancements</li>
</ul>

<hr>

<h2>Contact</h2>
<ul>
    <li><strong>Author:</strong> I.M. Nagi</li>
    <li><strong>Email:</strong> eslamnagi144@gmail.com</li>
    <li><strong>GitHub:</strong> <a href="https://github.com/IslamNagi14">IslamNagi14</a></li>
</ul>

</body>
</html>
