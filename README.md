
# Design and Implementation of Smart Waste Bin and Waste Monitoring Using Internet of Things and Machine Learning

## Overview
This project encompasses the development of a Smart Waste Bin system, integrating Internet of Things (IoT) and Machine Learning (ML) technologies. It features two main components: a waste level monitoring module and a waste classification module using the ESP32 microcontroller. This README outlines the system's functionality, current status, and future development plans.

### Waste Level Monitoring
- **Functionality**: Automatically monitors the waste level in bins.
- **Arduino Code**: Available in the repository.
- **Hardware Requirements**: Utilizes sensors and IoT modules compatible with Arduino.

### Waste Classification
- **Functionality**: Employs ML to classify types of waste.
- **Training Method**: Utilized the Edge Impulse tool for model training.
- **Deployment**: Deployed as an Arduino library on ESP32.
- **Dataset**: Trained with a custom dataset of around 300 images.
- **Model Accuracy**: Approximately 62% accuracy achieved.
- **Performance**: Accurate detection capabilities, with noted initial delays.

## Current Implementation and Testing
- The waste classification system has been rigorously tested, demonstrating precise detection capabilities. However, initial detection is subject to delays.

## Future Enhancements
1. **Expanded Dataset**: Increasing the dataset size for training to enhance model accuracy and reduce detection latency.
2. **Code Optimization**: Optimize the existing codebase for improved performance and quicker response times.
3. **Integrated System Design**: Combine waste level monitoring and classification functionalities, ensuring efficient memory usage in ESP32.
4. **Hardware Upgrades**: Explore advanced sensors and IoT modules for superior system performance.

## Installation and Usage
- Detailed setup instructions for ESP32 with the Arduino codes are provided in the supplementary documentation.
- Ensure all required libraries and dependencies are installed prior to running the codes.

## Contributing and Support
- Contributions to this project are welcome. Please adhere to the contribution guidelines provided.
- For support and further queries, please refer to the 'Issues' section of this repository.

## License
- This project permits open-source utilization and adaptation.

### Note
This README is crafted for junior students and other interested parties, offering a detailed overview and guiding principles for the Smart Waste Bin and Waste Monitoring project.
