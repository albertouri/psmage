# Procedural Starcraft MAp GEneration (PSMAGE)

Tool to generate StarCraft BroodWar maps.

## Dependencies

*   [Qt libraries 4.8.4 for Windows (VS 2008)][1]

    Set following environment variables (right click on My Computer, then Properties, Advanced, Environment variables): 

        QTDIR to C:\Qt\4.8.4 (or whatever path you installed QT)
        PATH, add C:\Qt\4.8.4\bin

## Utilities

* [MPQ Archives][4]
* [ScmDraft 2][7] ("ScmDraft2.exe -profile=Default" to avoid select profile each time)

## References

* CHK FILE FORMAT ([Specifications 1][11], [Specifications 2][12])
* Voronoi Diagrams
* [Perlin noise][10]
* [Poisson disk sampling][9]
* [Polygonal Map Generation for Games][2]
* [Tool: Starcraft 2 Map Analyzer][3]
* [StarCraft maps to Warcraft III maps][5]
* [Making StarCraft Maps][6]
* [Guide - Map Making][13]
* [StarCraft Terrain mechanics][8]

[1]: http://releases.qt-project.org/qt4/source/qt-win-opensource-4.8.4-vs2008.exe
[2]: http://www-cs-students.stanford.edu/~amitp/game-programming/polygon-map-generation
[3]: http://www.jamesjenista.com/2012/01/tool-starcraft-2-map-analyzer.html
[4]: http://www.zezula.net/en/mpq/download.html
[5]: http://mr-nutz.no-ip.org/Valentin/projets.php?page=5
[6]: http://www.teamliquid.net/forum/viewmessage.php?topic_id=95404
[7]: http://www.stormcoast-fortress.net/downloads/scmdraft2ZIP/
[8]: http://www.staredit.net/starcraft/Terrain
[9]: http://devmag.org.za/2009/05/03/poisson-disk-sampling/
[10]: http://devmag.org.za/2009/04/25/perlin-noise/
[11]: http://quantam.devklog.net/CHKFormat.htm
[12]: http://www.staredit.net/wiki/index.php/Scenario.chk
[13]: http://www.teamliquid.net/forum/brood-war/95409-guide-map-making