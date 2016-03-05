# Photon setup instructions

Generally there is a lot of help available online from the Particle Website as well as various online communities. This is just a rough guide, if anything doesn't work check the Troubleshooting below or failing that please look online.

 - [Sign up for Particle Account](https://build.particle.io/signup)
 - Power up Photon, if not in listening mode (blinking blue, hold down MODE button until it's blinking blue)
 - To setup and register device, either install Particle App on Smart Phone follow instructions in the App or set it up via command line (Photon needs to be connected by USB to computer).
 - Phone: follow the instructions in the Particle App
 - USB:
    - Install [Node.js](https://nodejs.org/en/)
    - Open a terminal and install the Particle Command Line
      - `sudo npm install -g particle-cli`
      - `sudo npm update -g particle-cli` (if already installed)
    - Run `particle setup` and follow command line instructions

#### First test

 - In the Particle online platform [build.particle.io](https://build.particle.io), you can now go to **Devices** at the bottom of the left hand menu (circle symbol) and should see your newly activated photon listed with a cyan pulsing dot (recognizing it is online), select it for flashing a program (the star).
 - Go to the code menu (**< >** symbol), **Create a new app** and paste the following code:
    ```
    int led = D7; // little on board LED
    void setup() {
        pinMode(led, OUTPUT);
    }

    void loop() {
      digitalWrite(led, HIGH);
      delay(1000);
      digitalWrite(led, LOW);
      delay(1000);
    }
    ```
  - **Verify** the code (checkmark), and **Flash** it to the photon (lightning bolt), it'll blink in different colors and then resume pulsing cyan but with the little blue onboard LED blinking on and off every second.
  - Have fun with more elaborate projects!

#### Coding platforms

You can either use the online Particle Build interface at [build.particle.io](https://build.particle.io) described above or use the [Atom](http://atom.io) based IDE [Particle Dev](https://www.particle.io/dev), which works very nicely for more complex projects but requires downloading any included libraries and still flashes via the cloud. For additional information on offline compilation options using the dfu bootloader directly, check out this helpful [tutorial](https://learn.sparkfun.com/tutorials/photon-development-guide/all).

## Examples and documentation

There are some very helpful code examples in the [firmware core library](https://docs.particle.io/reference/firmware/core/) at. Additionally, keep in mind the [C++](http://www.cplusplus.com/reference/cstring/strlen/) reference for great examples and lists of available functions.

A very useful feature of the photon is that registered Spark.functions can be triggered remotely through HTML POST commands on a web page or also via the `particle call` command line calls (also remotely!), check out [this example](https://docs.particle.io/guide/getting-started/examples/core/#use). Likewise, the photon can register information and events online in the cloud or respond to events by other photons.

## Troubleshooting information

- **Doesn't take any commands / trouble claiming the photon**: make sure to start from scratch, photon might have gotten corrupted and need to be factory reset, just hold both the setup and reset button pressed until it starts going through series of LED colors and ends on white, then let go. Reinstall vis USB or phone Partcle app.

- **Fails to update properly**: one of the first things after installation is a firmware update. This usually happens via the wireless after setup but if there is any trouble with the internet connection or something else during the update process, this might not work well. Here's an easy way to do the [firmware upgrade via USB](https://docs.particle.io/support/troubleshooting/firmware-upgrades/photon/) (on Mac):
  - Install `dfu-util` via [mac ports](https://www.macports.org/) or [homebrew](http://brew.sh/) by running `sudo port install dfu-util` or `sudo brew install dfu-util`
  - While connected via USB, enter [dfu mode](https://docs.particle.io/guide/getting-started/modes/photon/#dfu-mode-device-firmware-upgrade-) on the photon by holding both **RESET** and **SETUP**, releasing only **RESET** and waiting for yellow flashing (first flashes magenta) then also release **SETUP**
  - run `particle update` from command line
