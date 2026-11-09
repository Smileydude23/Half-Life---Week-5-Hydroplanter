# Half-Life---Week-5-Hydroplanter
A plant waterer that uses moisture sensors to detect when the plant needs watering, then a pump will pump water from a bowl/bottle of water to the plant. The design was made in KiCad and the code was made in Arduino IDE. I made this project because my plant, Dusty, is in need of consistent watering and it suffers a lot from when I leave the house for extended periods of time, like when I am camping. The PCB is built around an ESP32-C3 microcontroller. It monitors soil moisture and water level, controls a pump through a MOSFET, manages battery charging and protection, and displays status information on an OLED. The wiring is really trash because I'm bad at wiring but it should work. The Arduino firmware I wrote monitors soil moisture and water-tank availability, displays the plant’s moisture level on an OLED screen, and automatically controls a pump. It starts watering when the soil moisture falls to 30% or below, stops at 55%, and includes safety limits for an empty tank, a 15-second maximum runtime, and a 10-minute delay between watering cycles. It also averages multiple soil-sensor readings, converts them into a 0–100% moisture value, and shows the plant graphic, status, and sensor data on the display.

## Bill of Materials

| Part | Qty | Unit Price (USD) | Total (USD) | Vendor |
| :--- | :---: | :---: | :---: | :--- |
| **1/4" Vinyl Tubing** <br> | 1 | $3.83 | $3.83 | Temu |
| **0.96-inch OLED Display Module I2C** <br> | 1 | $1.98 | $1.98 | Temu |
| **2pcs/lot 18650 Battery Case** <br> | 1 | $1.44 | $1.44 | Temu |
| **MF-RHT050-0** <br> | 2 | $1.87 | $3.74 | Digikey |
| **SS14** <br> | 3 | $1.38 | $4.14 | Digikey |
| **USB4125-GF-A** <br> | 1 | $0.64 | $0.64 | Digikey |
| **IRLZ44NPBF** <br> | 1 | $2.02 | $2.02 | Digikey |
| **FS8205A** <br> | 1 | $0.69 | $0.69 | Digikey |
| **MFR-25FTF52-1K5** <br> | 2 | $0.21 | $0.42 | Digikey |
| **MFR-25FBF52-732K** <br> | 1 | $0.11 | $0.11 | Digikey |
| **DW01A** <br> | 1 | $0.11 | $0.11 | Digikey |
| **BQ24074RGTR** <br> | 1 | $2.73 | $2.73 | Digikey |
| **SMD IC MT3608** <br> | 1 | $0.29 | $0.29 | Digikey |
| **K104K15X7RF53L2** <br> | 2 | $0.57 | $1.14 | Digikey |
| **FK22X7R1E475K0000** <br> | 1 | $1.63 | $1.63 | Digikey |
| **S3B-PH-K-S** <br> | 1 | $0.16 | $0.16 | Digikey |
| **S2B-PH-K-S** <br> | 2 | $0.26 | $0.52 | Digikey |
| **78F4R7J-RC** <br> | 1 | $0.25 | $0.25 | Digikey |
| **I13991054** <br> | 1 | $1.21 | $1.21 | Aliexpress |
| **SEN0193** <br> | 1 | $6.21 | $6.21 | Digikey |
| **4547** <br> | 1 | $3.31 | $3.31 | Digikey |
| **PLS-03IA-3PAI** <br> | 1 | $3.19 | $3.19 | Digikey |
| **50YXJ22MTA5X11** <br> | 1 | $0.28 | $0.28 | Digikey |
| **PCB Manufacturing** <br> | 1 | $4.00 | $4.00 | JLCPCB |
| **Tax & shipping** <br> | — | — | $17.08 | — |
| **Total Funding Used** | — | — | **$61.12 / $65** | |

<img width="800" height="787" alt="Screenshot 2026-11-07 181000" src="https://github.com/user-attachments/assets/0d1b86e0-8110-4b8e-8540-70c8102d9ba9" />
<img width="1115" height="832" alt="Screenshot 2026-11-07 180919" src="https://github.com/user-attachments/assets/171a387f-5155-4532-8b52-8fc4ab311c49" />
<img width="826" height="757" alt="Screenshot 2026-11-07 170209" src="https://github.com/user-attachments/assets/16b13838-f18c-4d73-96a7-c10018e75469" />
<img width="820" height="777" alt="Screenshot 2026-11-07 170149" src="https://github.com/user-attachments/assets/bfc373b8-c6bf-4de2-b83d-24ea4dcae584" />
<img width="737" height="527" alt="Screenshot 2026-11-08 013754" src="https://github.com/user-attachments/assets/93dad28b-3ca6-421c-8da9-f60ecd8ccd4d" />
<img width="6838" height="17163" alt="DigiKey - Shopping Cart " src="https://github.com/user-attachments/assets/3a13d2b8-c521-4845-aac2-612906faec30" />
<img width="995" height="332" alt="Aliexpress" src="https://github.com/user-attachments/assets/a00f7724-69ce-4804-a351-48101d02af0b" />
<img width="1183" height="667" alt="Temu" src="https://github.com/user-attachments/assets/e1cb0f74-9e16-4e2a-9b2f-04ebfc786586" />
<img width="520" height="447" alt="JLCPCB" src="https://github.com/user-attachments/assets/1770f98a-9330-4dc4-b563-99c18a3be052" />

