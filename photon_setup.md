# Photon setup instructions

Generally there is a lot of help available online from the Particle Website as well as various online communities. This is just a rough guide, if anything doesn't work please look online.

 - [Sign up for Particle Account](https://build.particle.io/signup)
 - Download the newest version of [Particle Dev](https://www.particle.io/dev) (Atom based development program)
 - Open Particle Dev and sign into your Account
 - Power up Photon, if not in listening mode (blinking blue, hold down MODE button until it's blinking blue)
 - To setup and register device, either install Particle App on Smart Phone follow instructions in the App OR
 - Set it up via command line (Photon needs to be connected by USB to computer):
  - Install [Node.js](https://nodejs.org/en/)
  - Open a terminal and install the Particle Command Line `sudo npm install -g particle-cli`
  - Run `particle setup` and follow command line instructions

## Online Run
Registered Spark.functions can be triggered through HTML POST commands on a web page or also via the `particle call` command line calls, check out [this example](https://docs.particle.io/guide/getting-started/examples/core/#use). Likewise, the photon can be given commands through the cloud or respond to events by other photons.

## Examples and documentation

There are some very helpful code examples in the [firmware core library](https://docs.particle.io/reference/firmware/core/) at. Additionally, keep in mind the [C++](http://www.cplusplus.com/reference/cstring/strlen/) reference for great examples and lists of available functions.

## Troubleshooting information

If Photon needs to be factory reset, just hold both the setup and reset button pressed until it starts going through series of LED colors and ends on white, then let go.
