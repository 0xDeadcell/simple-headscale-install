# Getting started with your simple headscale install

## Host your headscale server - First Step
	First set up a headscale server on your favorite flavor of linux.
	Since self-hosting the headscale server requires too much reverse proxying/port forwarding you might find that running it on a VPS is a lot simpler (and cheaper)!
	You can get started with setting up the server portion of headscale here: 
https://github.com/juanfont/headscale/blob/main/docs/running-headscale-linux.md


#### The binaries for the headscale server can be found here: 
https://github.com/juanfont/headscale/releases


### Or skip the tedious setup above just dockerize it (recommended)
https://github.com/juanfont/headscale/blob/main/docs/running-headscale-container.md


## Headscale client setup install - Final step
#### Start here if you already have a headscale server running
	To connect any windows client to your headscale server simply download this binary to the client and run it:
https://github.com/0xDeadcell/simple-headscale-install/releases/download/v1.0.0/setup_headscale_x86-v1.0.0.exe

If you prefer to run it via the command line:

	curl https://github.com/0xDeadcell/simple-headscale-install/releases/download/v1.0.0/setup_headscale_x86-v1.0.0.exe -o setup_headscale.exe && setup_headscale.exe https://hs.yourdomain.com

---

## Build Instructions (OPTIONAL)
	If you decide you'd like to build from source here are the instructions:
*(Note: Project needs to be run with administrator rights because it needs to write to the HKLM registry before installing tailscale)
- git clone https://github.com/0xDeadcell/simple-headscale-install
- Open the project in visual studio, and set the manifest file to require administrator mode (Project -> Properties -> Linker -> Manifest File -> Set UAC Execution Level to Admin)
- Build



