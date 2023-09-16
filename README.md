# LED_2812B

WCMCU-2812B LED control
<h1>Description</h1>
<p>This project uses the folowing main hardware components:</p>
<ol>
  <li>Curiosity 2.0 PIC32MZ EF</li>
  <li>String of several WCMCU2812-B RGB LED</li>
</ol>

### How does it works...

A Python based desktop application sends the following information to the microcontroller:

1. The number of data bytes to be expected.
2. A command (CMD_0) for the microcontroller to enter in *"Transfer Mode"*.
3. The bytes array representing the encoded form of GRB colors (in this order), for all LEDs.

#### LED color encoding

For each LED there are be 3 data bytes representing the intensity of Green, Red and Blue colors.

Each bit of color intensity bytes is encoded with 4 bits in final form (that will be transfered to LEDs). In the end, a singe LED will need 12 bytes to be encoded.

Encoding:
- bit 0 is **0100**
- bit 1 is **0110**

#### Example 1

Let's say that we have to set LED with color 0xFF00FF (which is <span style="color:#FF00FF;">purple</span>).
<table>
  <tr><th>Color</th><th>Value</th><th>Byte</th><th></th></tr>
  <tr><td>Green</td><td>0</td><td>0</td>
    <td>
      <table>
        <tr><td></td><th>b7</th><th>b6</th><th>b5</th><th>b4</th><th>b3</th><th>b2</th><th>b1</th><td>b0</th></tr>
        <tr><td>+0</td><td>0</td><td>1</td><td>0</td><td>0</td><td>0</td><td>1</td><td>0</td><td>0</td></tr>
        <tr><td>+1</td><td>0</td><td>1</td><td>0</td><td>0</td><td>0</td><td>1</td><td>0</td><td>0</td></tr>
        <tr><td>+2</td><td>0</td><td>1</td><td>0</td><td>0</td><td>0</td><td>1</td><td>0</td><td>0</td></tr>
        <tr><td>+3</td><td>0</td><td>1</td><td>0</td><td>0</td><td>0</td><td>1</td><td>0</td><td>0</td></tr>
      </table>
    </td>
  </tr>
  <tr><td>Red</td><td>255</td><td>4</td>
    <td>
      <table>
        <tr><td></td><th>b7</th><th>b6</th><th>b5</th><th>b4</th><th>b3</th><th>b2</th><th>b1</th><td>b0</th></tr>
        <tr><td>+0</td><td>0</td><td>1</td><td>0</td><td>0</td><td>0</td><td>1</td><td>0</td><td>0</td></tr>
        <tr><td>+1</td><td>0</td><td>1</td><td>0</td><td>0</td><td>0</td><td>1</td><td>0</td><td>0</td></tr>
        <tr><td>+2</td><td>0</td><td>1</td><td>0</td><td>0</td><td>0</td><td>1</td><td>0</td><td>0</td></tr>
        <tr><td>+3</td><td>0</td><td>1</td><td>0</td><td>0</td><td>0</td><td>1</td><td>0</td><td>0</td></tr>
      </table>
    </td>
  </tr>
  <tr><td>Blue</td><td>255</td><td>8</td>
    <td>
      <table>
        <tr><td></td><th>b7</th><th>b6</th><th>b5</th><th>b4</th><th>b3</th><th>b2</th><th>b1</th><td>b0</th></tr>
        <tr><td>+0</td><td>0</td><td>1</td><td>0</td><td>0</td><td>0</td><td>1</td><td>0</td><td>0</td></tr>
        <tr><td>+1</td><td>0</td><td>1</td><td>0</td><td>0</td><td>0</td><td>1</td><td>0</td><td>0</td></tr>
        <tr><td>+2</td><td>0</td><td>1</td><td>0</td><td>0</td><td>0</td><td>1</td><td>0</td><td>0</td></tr>
        <tr><td>+3</td><td>0</td><td>1</td><td>0</td><td>0</td><td>0</td><td>1</td><td>0</td><td>0</td></tr>
      </table>
    </td>
  </tr>
</table>
