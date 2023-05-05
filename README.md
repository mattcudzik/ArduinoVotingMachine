# ArduinoVotingMachine

Software made for my arduino project consisting of lcd display and 5 buttons.

## Features:
<ul>
<li>User votes for one of 4 options using buttons.</li>
<li>Winner of the vote is displayed at the end of voting with number of votes collected.</li>
<li>Ability to change initials of voting candidates.</li>
<li>History of 10 last votings (kept in RAM, so no permament storage).</li>
<li>Simple device settings like turning on/off display backlight.</li>
</ul>

## Electronics schematic:
<img src="https://user-images.githubusercontent.com/62482303/236430248-c152ab92-6724-4dde-8652-431db9cafa4b.png">

Display is connected to arduino via I2C. Buttons use internal pullup resistor but ideally there should be another external one for each button.

