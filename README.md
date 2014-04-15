Pteridophyta
============

Game Cycle 3
<pre><code>
So..
									  Game												
										|												
			+---------------------------+---------------------------+
			|							|							|
		GameStage					GameStage					GameStage				
			|							|							|
	+-------+-------+           +-------+-------+			+-------+-------+
	|				|			|			    |			|				|
Component		Component	Component		Component	Component		Component		
</code></pre>


Game 	  <---Only one of these (GameClient or GameServer). Game will transition to the next GameStage, 
			  when the currently running GameStage indicates it is done.
			  
GameStage <---Each Game has N GameStage. GameStage run one at a time. GameStage own their life cycle, 
			  they decide when they are done.
			  
Component <---Each GameStage has M Components. Every component that a GameStage owns is executed each life cycle. 

QuadTree for Broad phase collision
* http://en.wikipedia.org/wiki/Quadtree

SAT for Narrow phase collision
* http://www.metanetsoftware.com/technique/tutorialA.html
* http://www.sevenson.com.au/actionscript/sat/
* http://www.codezealot.org/archives/55

<pre><code>

///SAT Pseudo Code
make a list of edges for p1
make a list of edges for p2
make a list of normals (one for each edge, for each polygon. normals from both polygons can be kept in the same list)

For each normal
  For each p1 edge
    project edge onto normal
    if new min or max projection then 
	  save
  For each p2 edge
    project edge onto normal
    if new min or max projection then
      save
  if interval(p1 min, p1 max) overlaps interval(p2 min, p2 max) then
      continue
  else
      break
	  
	  
///Game Loop Pseudo Code
On Client:
	During Initialize:
		Load TMX Map
		Array 	 Background
		Array 	 Foreground
		QuadTree Walkables
		Quadtree Gravity Zones
		Quadtree Dynamics
		
	During Local Inputs:
		Update List of Commands
	
	During Remote Event:
		Update List of Remotes
	
	During Update:
		For each d in Dynamics
			Retrieve Relevant Walkables
			Retrieve Relevant Gravity Zones
			Based on current Gravity, Rotate d if needed
			update position using Commands and Remotes
			collision detect with walkables, and correct if needed
			collision detect with dynamics, and apply damage if needed
</code></pre>



'Tiled' is an Open Source Level Editor for Tile based Games.
It has an output format called TMX. LoaderTMX is able to load a TMX file.
* https://github.com/bjorn/tiled/wiki/TMX-Map-Format
* http://gamedevelopment.tutsplus.com/tutorials/parsing-and-rendering-tiled-tmx-format-maps-in-your-own-game-engine--gamedev-3104


Requirements
* Code::Blocks - I have been quite pleased.
  * http://www.codeblocks.org/
* gcc >=4.8 
  * http://www.mingw.org/
* Cmake - for building SFML, SFGUI, and others.
  * http://www.cmake.org/
* SFML 2.1
  * http://www.sfml-dev.org/download/sfml/2.1/
* SFGUI 0.2.3
  * git clone https://github.com/TankOs/SFGUI.git
  * http://sfgui.sfml-dev.de/download/
* GLEW 1.10.0
  * http://glew.sourceforge.net/
* Expat 2.1.0
  * http://expat.sourceforge.net/
* Tiled 0.9.1
  * http://www.mapeditor.org/

Pending Requirements
* Lua ?.?
  * http://www.lua.org/download.html
* Box2D ?.?
  * http://box2d.org/


What?
* Phase 3
* A Multiplayer 2D game.
* Networking
* Tile engine
* Tile editor
* Scriptable
* Written in C++ because it's cooler than you or I.
* Previous Phases
  * https://github.com/Hibchibbler/TankGame - Phase 2
  * https://github.com/Hibchibbler/SimpleGame - Phase 1