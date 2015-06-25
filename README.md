# slackbutton

An Internet Button using **Particle Core** and **Slack**, done for fun and profit. Mostly <s>profit</s> fun.

## You'll need

* A [Spark Core](https://store.particle.io) (aka Particle Core, or a Photon, once it's out)
* A momentary tactile switch, ie a big honking Button (get one with a LED inside because they're cool)
* A 10 kΩ resistor (which you can probably leave out if you don't have one)
* An account on a [Slack](https://www.slack.com) server
* [The Particle CLI](http://docs.particle.io/core/cli/#installing)
* A couple of hours of quality time

## How to do it

Connect the big honking Button between the Core's +3.3V pin (voltage out) and any digital pin. I used D0 before reading that it's usually used for serial communication. Connect the 10 kΩ resistor between the same digital pin and GND on the Core.

Go to your Slack server and create an Incoming Webhook integration. To do so, drop down the menu next to your name in the Slack interface and choose **Configure integrations**, then filter or scroll to **Incoming Webhooks** and press New. You probably want to post to your #test channel or similar. Copy the Webhook URL, and press Save.

Fork this repository and open the code in your editor, or copy-paste it into the web IDE. Who knows, it might even be possible to fork it straight into the web IDE.

Edit the slackbutton.json file and paste the Webhook URL to the "url" value. The `"mydevices": "true",` bit should ensure that only your buttons can post to your Slack, but if you want to be really sure about things, add `"deviceID": "the-long-id-of-your-device",` to the slackbutton.json and nobody else can post as your button.

Now, edit the slackbutton.ino file to change the button pin and the snarky message in the `Spark.publish("slackbutton", "...")` line in the `loop()`, if so required.

Switch to your command line window and create a [Particle web hook](http://docs.particle.io/core/webhooks/) with `particle webhook create slackbutton.json` (if you don't have the Particle CLI installed, do so with `$ npm install -g particle-cli
&& particle login`).

Flash the Core. You can either use the [Web IDE](https://build.particle.io) or the rather nifty Atom fork [Particle Dev](http://docs.particle.io/core/dev/) (if these synchronized the code between each other... now _that_ would be nifty!). Or use the Particle CLI if you're really hard core.

Wait a minute, then press the button and watch the Slack channel. You can also check out the [Particle dashboard](https://dashboard.particle.io/user/logs) to see whether your presses get through.

Profit!

Most of the code is actually just ancillary to the beef. Much of the button pushing logic is actually just there to make sure a button press is really happeining and not a glitch (_Debounce_, and here implemented rather naïvely that a button press must be longer than 50 milliseconds), or that only one button press is sent, regardless how long you push the button. Once a day, the Core will [update its internal clock](http://docs.particle.io/core/firmware/#spark-synctime) from the Particle Cloud. Once an minute, the button will phone home to say [it's](http://docs.particle.io/core/firmware/#get-device-name) still alive. You can safely omit these bits if you're not going to run your Slackbutton for extended periods of time.
