## 序言
本文仅用于记录对此产品的开发过程与思考，具体的产品详细介绍请看我的博客项目专栏： [YeMing - 可调功率定时器](https://www.charlesyu1997.com/wiki/MultiTimer/index.html)

## 功率模块
该部分主要通过读取当前电位器输入的模拟信号值（ADC读取）以及当前功率状态开关的状态，来传输相应的输出值给到功率输出模块。同时将输出值实时显示在数码管上。

### 所用变量及创造函数

#### variable

- power output status: 
```C
enum_PowerStatusTypeDef global_power_status
``` 
- adc value: 
```
uint16_t adc_data
```

#### functions

- Determining_Power_Output_Status
```C
/**
* @name       Determining_Power_Output_Status
* @brief      To determine the status of power output
*             and the corresponding actions.
* @param      NONE
* @return     NONE
*
*/
void Determining_Power_Output_Status(void)
```
- Get_ADC_Value_And_Calculate
```C
/**
* @name       Get_ADC_Value_And_Calculate
* @brief      Get the voltage of potentiometr
*             and return the calculated power output percentage.
* @param      NONE
* @return     float
*
*/
float Get_ADC_Value_And_Calculate(void)
```












