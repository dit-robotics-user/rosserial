/*
 * main.cpp

 *
 *  Created on: 2018/01/17
 *      Author: yoneken
 */
#include <mainpp.h>
#include <ros.h>
#include <std_msgs/Float32MultiArray.h>

ros::NodeHandle nh;

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
    nh.getHardware()->flush();
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    nh.getHardware()->reset_rbuf();
//    nh.subscribe(rx_callback);
}

float tx_buffer[1]={8};
float rx_buffer[1];

std_msgs::Float32MultiArray tx_data;
std_msgs::Float32MultiArray rx_data;

void rx_callback(const std_msgs::Float32MultiArray &data) {
    memset(rx_data.data, 0, 1 * sizeof(float));
    memcpy(rx_data.data, data.data, data.data_length * sizeof(float));
    rx_data.data_length = data.data_length;
}

ros::Publisher                               pub("from_st1", &tx_data);
ros::Subscriber<std_msgs::Float32MultiArray> sub("to_st1", rx_callback);

void rosserial_init(void) {
    nh.initNode();
    nh.advertise(pub);
    nh.subscribe(sub);
    tx_data.data        = tx_buffer;
    rx_data.data        = rx_buffer;
    tx_data.data_length = 1;
}

void rosserial_task(void) {
    pub.publish(&tx_data);
    nh.spinOnce();
}
void roslog() {
    nh.loginfo("start");
}
