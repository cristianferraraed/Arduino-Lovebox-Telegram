# Arduino-Lovebox-Telegram
n this project, I've developed a system that uses an ESP32 microcontroller to connect to the internet via Wi-Fi. with Telegram's API to receive messages sent to a specific bot. 
Project Overview
In this project, I've developed a system that uses an ESP8266 microcontroller to connect to the internet via Wi-Fi. The core functionality of this system is to interact with Telegram's API to receive messages sent to a specific bot. Whenever a message is sent to my Telegram bot, the ESP8266 fetches it and displays it on a connected device. In addition to a standard LCD screen, I've incorporated an 8x8 LED matrix to visually enhance the display of notifications or symbols associated with incoming messages.
![IMG_0814](https://github.com/user-attachments/assets/4d9725c6-c558-4a9e-8552-e81bed651c1f)

System Components
ESP8266: This is the brain of the operation, handling both the Wi-Fi connection and the application logic.
LCD Display: Used for displaying the received messages. "New message from Cristian" followed by the message text is shown here.
8x8 LED Matrix: Adds a dynamic visual element, displaying simple icons or animations when messages are received, providing quick visual cues.
LED: A simple LED provides immediate visual feedback for incoming messages, lighting up briefly with each new message.
Telegram Bot: Serves as the interface for sending messages to the device. Users can interact with the bot from anywhere in the world as long as they have internet access.
Features
Wi-Fi Connectivity: The device automatically connects to the specified Wi-Fi network.
Message Retrieval: Periodically queries Telegram's API to check for new messages.
Message Display: Messages are displayed on the LCD display and remain visible until the next message arrives.
Visual Notification: An LED lights up to signal the arrival of new messages, complementing the textual display on the LCD.
Dynamic Visuals on Matrix: The 8x8 matrix displays relevant icons or animations related to the content of messages, enhancing the interactivity and engagement of the notification system.
Use Case Scenarios
This system is ideal for environments where instant physical display of messages is necessary, without the need to check mobile devices or computers. Examples include:

Workplace Notifications: Where staff need to be promptly informed without the use of mobile phones or computers.
Smart Home Systems: For receiving Telegram-based notifications and commands which can then trigger further actions within a home system.
Educational or Laboratory Settings: Where messages can be sent to specific devices as part of experiments or demonstrations.
Conclusion
This project merges hardware and software to create a versatile and immediate communication system, leveraging the popularity and accessibility of Telegram's APIs to interface with the external world through text messages. The addition of the 8x8 LED matrix brings a new layer of engagement, making the system not only functional but also visually captivating.
<img width="675" alt="Screenshot 2024-11-14 alle 03 09 51" src="https://github.com/user-attachments/assets/0f21b984-aa9d-441b-9589-efd7ac9cace9">

<img width="402" alt="Screenshot 2024-11-14 alle 03 01 08" src="https://github.com/user-attachments/assets/800b8de2-f516-44a5-b1de-e5168efbe171">
