/*
 * Javascript based IRC bot, with some AI awesomeness *
 * Depends on node.js though. I dont own the libraries here *
 * need sqlite3 support with a bit of python madness 
 */

/* Libraries includes */
var irc = require('./lib/irc');
var color = require('./lib/colors');
var codes = require('./lib/codes');
var http = require('http');

/* System Includes */
var assert = require('assert'),

/* Bot Configs */
var __bot_config = /* I m just obssed with id's */
{
    'error':'DownTime',
    'bot' : 
    [
	{'id':'0',
	 'profile':
	 {
	     'name':'mzbot',
	     'identity':'Batman',
	     'place':'Bangalore,India',
	     'dateofbirth':'24-May-2013',
	     'owner':'Linux Guy',
	     'About':'Well, bot if you see..',
	     'channels':['#emacs','#linux'],
	 },
	},
	{'id':'1',
	 'profile':
	 {
	     'name':'csbot',
	     'identity':'Alfred',
	     'place':'Bangalore,India',
	     'dateofbirth':'24-May-2013',
	     'owner':'Humanoid',
	     'About':'Well, bot if you see..',
	     'channels':['#linux','#emacs'],
	 },
	},
    ],
}

/* Initialize bot */
var bot = {};

var date = new Date();
var curr_hour = date.getHours();
var curr_min = date.getMinutes();
var curr_sec = date.getSeconds();
var curr_msec = date.getMilliseconds();

var blue  = '\033[34m';

var client = new irc.Client('irc.something.com', __bot_config.bot[0].profile.name, {channels: __bot_config.bot[0].profile.channels,debug: true});

/* Crape Diem, need handlers for each of the channels */

var channel = __bot_config.bot[0].profile.channels[1];

client.addListener('error', function(message) { console.log('error: ', message) });

client.addListener('pm', function (from, message) {client.say(channel, "Hello, " + from + " Whats up?");});

client.addListener("join", function () {client.say(channel,"Hello everyone!");});

client.addListener("message" + channel, function(nick,text) 
		   {
		       if(text.search(/(help|Help)/)!= -1)
		       {
    			   client.say(channel, "Hello Help topics are Mr. " + nick +" Try Hi,Hello,time,lunch,montezuma,mzombie,montshare,mzomshare,planlunch");
		       }
		       if(text.search(/(hi|Hi|Hello|hello)/)!= -1)
		       {
			   client.say(channel, "Hello " + nick + "!,What's up?");
		       }
		       if(text.search(/(time|Time)/)!= -1)
		       {
			   client.say(channel,"Time is "+ curr_hour + ":" + curr_min + ":"+ curr_sec + ":" + curr_msec + " Mr. "+ nick );

		       }
		       if(text.search(/(About|about)/)!= -1)
		       {
			   client.say(channel,"Mzbot is the Javascript-Bot written on the nodejs libraries. The most important being the irc and the require library");
		       }
		       if(text.search(/(Linux|linux)/)!= -1)
		       {
			   client.say(channel,"Defines my birth on planet Earth, Linux is a derived Operating System from its fore-fathers Unix");
		       }
		       if(text.search(/(GNU|gnu)/)!= -1)
		       {
			   client.say(channel,"GNU, GNU's Not Unix!!, Based on GNU Hard Kernerl, Stallman says -> 'GNU as technical means to social ends'");
		       }
		       if(text.search(/(GRUB|grub)/)!= -1)
		       {
			   client.say(channel,"Grand Unified Boot Loader, Well now we have EFI, UEFI as well");
		       }
		   });

var echannel = __bot_config.bot[0].profile.channels[0];

client.addListener('error', function(message) { console.log('error: ', message) });

client.addListener('pm', function (from, message) {client.say(echannel, "Hello, " + from + " Whats up?");});

client.addListener("join", function () {client.say(echannel,"Hello everyone!");});

client.addListener("message" + echannel, function(nick,text) 
		   {
		       if(text.search(/(help|Help)/)!= -1)
		       {
    			   client.say(echannel, "Hello Help topics are Mr. " + nick +" Try Hi,Hello,time,emacs,Love,awesomeness");
		       }
		       if(text.search(/(hi|Hi|Hello|hello)/)!= -1)
		       {
			   client.say(echannel, "Hello " + nick + "!,What's up?");
		       }
		       if(text.search(/(time|Time)/)!= -1)
		       {
			   client.say(echannel,"Time is "+ curr_hour + ":" + curr_min + ":"+ curr_sec + ":" + curr_msec + " Mr. "+ nick );
			   
		       }
		       if(text.search(/(About|about)/)!= -1)
		       {
			   client.say(echannel,"Mzbot is the Javascript-Bot written on the nodejs libraries. The most important being the irc and the require library");
		       }
		       if(text.search(/(emacs|Emacs)/)!= -1)
		       {
			   client.say(echannel,"Emacs.. We are invaders of this world");
		       }
		       if(text.search(/(GNU|gnu)/)!= -1)
		       {
			   client.say(echannel,"GNU, GNU's Not Unix!!, Based on GNU Hard Kernerl, Stallman says -> 'GNU as technical means to social ends'");
		       }
		       if(text.search(/(GRUB|grub)/)!= -1)
		       {
			   client.say(echannel,"Grand Unified Boot Loader, Well now we have EFI, UEFI as well");
		       }
		   });

