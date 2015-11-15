# Setting up data logging from a Spark/Particle (e.g. Photon) or networked Arduino using google spreadsheets

## HTTPS forwarding

Secure transmissions (HTTPS) are required by google docs these days but are a bit tricky because they require a lot of computation and memory for all the added security layers. Instead, its easier to use an HTTPS forwarding service, which is described very nicely how to set up in the [Google Forums](https://productforums.google.com/forum/#!topic/docs/f4hJKF1OQOw). This is just a summary of information gathered there and elsewhere, all credit goes to the original posters of this solution.

 - Create a new Google Spreadsheet and go to `Tools -> Create Form` to add the fields you are interested in recording (Timestamp is automatically included)
 - Select `Responses -> Get pre-filled URL` from the menu
 - Enter easy placeholders for each filled (e.g. value1, value2, value3, value4, etc.) and hit `Submit`
 - Copy the generated link and replace the portion that says `viewform?` with `formResponse?ifq&` and add `&submit=Submit` to the end of the URL (see [this article](http://justingale.com/2013/09/url-tricks-for-google-forms-pre-populate-and-automatically-submitting-responses/) for details)
 - Executing this URL in a browser will generate a line in your spreadsheet with the pre-filled test values (value1, value2, etc.) - check that this works (otherwise there might be a mistake in your URL or Google has changed the format again).
 - Sign up for [Pushing Box](https://www.pushingbox.com) using your Gmail Account
 - Go to `My Services -> Add a service -> CustomURL` and add the beginning of your Google URL (starting with `https://docs.google.com...`) up until and including the `formResponses` part as `Root URL`, and choose `GET` as the `Method`.
 - Go to `My Scenarios -> Create a scenario or add a device`, enter a name of your choice (e.g. `Data Logger`) and hit `Add`, then `Add an action -> Add an action with this service` for the `CustomURL` you just created.
 - For `Data`, add the rest of your URL starting with `?ifq&entry...` all the way through the end `...&submit=Submit` and replace all the pre-filled value place holders you entered earlier (value1, value2, etc.) with variable place holders in between `$` signs (whatever names you find useful, e.g. `$var1$`, `$var2`, etc.). Your URL should then have a bunch of chained `&entry.XXXXXXX=$varX$` between `?ifq&entry` and `&submit=Submit`.
 - Hit `Test scenario` and check your google spreadsheet. Hopefully, you'll have a new entry with the variable placeholders `$varX$` as new values.
 - Take note of the `DeviceID` for this new `Scenario` you just created and use it to construct your final URL to use from your Arduino or Photon: `http://api.pushingbox.com/pushingbox?devid=DeviceID&var1=value&var2=value&var3=value...` (replace the `DeviceID` with your device ID and the `varX` variable names with the ones you picked earlier - omit the `$` signs). You can test this URL with any test values for these variables (spreadsheet/form fields) you like.
  - Note: if the time stamp is off make sure to adjust your time zone in the spreadsheet under `File -> Spreadsheet Settings`

## Code

Simply change add the `DeviceID` in `gs_logging.ino` and adjust the variable names for your form to get some initial data in form of timestamp and the device name added ever couple of seconds to your google spreadsheet. This code snippet uses the [`HttpClient`](https://github.com/nmattisson/HttpClient) library and the HTTP request itself is largely based on the example provided therein.

## Troubleshooting

If you're running in the [particle cloud](https://build.particle.io), make sure that you're including the `HttpClient` library with `#include "HttpClient/HttpClient.h"` whereas in the [particle dev IDE](https://www.particle.io/dev) only flat folder structure was allowed at the time of this writing so you'll have to copy the firmware files from the [`HttpClient` library]([`HttpClient`](https://github.com/nmattisson/HttpClient) to the same folder as `gs_logging.ino` and include with `#include "HttpClient.h"`,
