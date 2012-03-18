#!/usr/bin/ruby
@input_name = 'map.txt'
@output_name = 'output.scx'
@types = {
  'chars' => 'A',  # not changed
  'bytes'  => 'C',  # one byte
  'int'   => 'S',  # small-endian int, 2 bytes
  'long'  => 'L',   # small-endian long, 4 bytes
  'bin'   => '*' # For importing static data settings
}
@b_string = ''

# Bring in defaults from other scx files
# Be sure to chop off a trailing EOL if needed
# perl -pe 'chomp if eof' filename
vcod = (File.open('vcod.bin', 'rb')).read
pupx = (File.open('pupx.bin', 'rb')).read
ptex = (File.open('ptex.bin', 'rb')).read
unix = (File.open('unix.bin', 'rb')).read
upgx = (File.open('upgx.bin', 'rb')).read
tecx = (File.open('tecx.bin', 'rb')).read

tile = []
map = File.open(@input_name, 'r') do |file|
  while (line = file.gets)
    line.each_char do |c|
      if c == "1"
        tile << 37 #low ground
      elsif c == "2"
        tile << 67 #high ground
      end
    end
  end
end

width = height = Math.sqrt(tile.length).to_i

puni = []; 5700.times { |x| puni << 1 }
unit = []; #214 (int) is starting location
isom = []; ((width/2 + 1)*(height+1)*4).times { |x| isom << 16 }
mask = []; (width*height).times { |x| mask << 255 }
str  = []; str << 1024; 1024.times { |x| str << 2050 }
uprp = []; 1280.times { |x| uprp << 0 }
upus = []; 64.times { |x| upus << 0 }
mrgn = []; 5100.times { |x| mrgn << 0 }
trig = []; 7200.times { |x| trig << 0 } #???
forc = []; 20.times { |x| forc << 0 }
wav  = []; 1024.times { |x| wav << 0 }
swnm = []; 256.times { |x| swnm << 0 }
colr = []; (0..7).each { |x| colr << x }
#pupx = []; 2318.times { |x| pupx << 1 } # 1 is default for last bytes
#ptex = []; 1672.times { |x| ptex << 1 } # 1 is default for last bytes
#unix = []; 4168.times { |x| unix << 1 } # 1 is default for first bytes
#upgx = []; 794.times { |x| upgx << 1 } # 1 is default for first bytes
#tecx = []; 396.times { |x| tecx << 1 }# 1 is default for first bytes
sections = [
  # Type of scenario file
  { 'name'=> 'TYPE', 'length'=> 4,    'val'=> 'RAWB', 'type'=> 'chars' },
  # File format version (205 for BW)
  { 'name'=> 'VER',  'length'=> 2,    'val'=> 205,    'type'=> 'int'   },
  # Additional format info (10 for current)
  #{ 'name'=> 'IVER', 'length'=> 2,    'val'=> 10,     'type'=> 'int'   },
  # Additional format info (replaces IVER, 11 for > 1.04/BW)
  { 'name'=> 'IVE2', 'length'=> 2,    'val'=> 11,     'type'=> 'int'   },
  # Verification code, imported
  { 'name'=> 'VCOD', 'length'=> vcod.length, 'val'=> vcod,   'type'=> 'chars' },
  # Designates controller for player, 06 = human
  { 'name'=> 'IOWN', 'length'=> 12,   'val'=>[6,6,6,6,6,6,6,6,0,0,0,0], 'type'=>'bytes' },
  # Designates controller for player, 06 = human (redundant with IOWN?)
  { 'name'=> 'OWNR', 'length'=> 12,   'val'=>[6,6,0,0,0,0,0,0,0,0,0,0], 'type'=>'bytes' },
  # Tileset ( 7 = twilight world)
  { 'name'=> 'ERA',  'length'=> 2,    'val'=>7,              'type'=>'int'   },
  # Dimensions
  { 'name'=> 'DIM',  'length'=> 4,    'val'=>[width, height], 'type'=>'int'  },
  # Species of players
  { 'name'=> 'SIDE', 'length'=> 12,    'val'=>[1,0,2,1,0,2,1,0,7,7,7,4], 'type'=>'bytes'  },
  # Graphical tile map, only different than TILE if doodads present
  { 'name'=> 'MTXM', 'length'=>tile.length * 2, 'val'=> tile, 'type'=>'int' },
  # UPGR (not used in other maps, not required?)
  # PTEC (not used in other maps, not required?)
  # Player unit restrictions, all 1s for normal defaults (5700 times)
  { 'name'=> 'PUNI', 'length'=>5700,   'val'=> puni, 'type'=>'bytes' },
  # Flags and stats of each unit on the map (only starting locations for this)
  { 'name'=> 'UNIT', 'length'=>0,     'val'=> unit, 'type'=>'chars' },
  # ISOM, maps isometric view in Staredit, other maps are all 16?
  { 'name'=> 'ISOM', 'length'=>isom.length*2, 'val'=>isom, 'type'=>'int' },
  # Tile map of level's terrain 
  { 'name'=> 'TILE', 'length'=>tile.length * 2, 'val'=> tile, 'type'=>'int' },
  # Doodad map of level (not using)
  { 'name'=> 'DD2',  'length'=>0, 'val' => '', 'type'=>'chars' },
  # Doodad to unit map
  { 'name'=> 'THG2',  'length'=>0, 'val' => '', 'type'=>'chars' },
  # Fog of war
  { 'name'=> 'MASK',  'length'=>mask.length, 'val' => mask, 'type'=>'bytes' },
  # Strings used. Zeroing out. 
  { 'name'=> 'STR',  'length'=>str.length*2, 'val' => str, 'type'=>'int' },
  # UPRP, triggers ???
  { 'name'=> 'UPRP',  'length'=>uprp.length, 'val' => uprp, 'type'=>'bytes' },
  # UPUS, trigger units, don't use
  { 'name'=> 'UPUS',  'length'=>upus.length, 'val' => upus, 'type'=>'bytes' },
  # MRGN Locations, docs say 256 locations, maps actually have 255
  { 'name'=> 'MRGN',  'length'=>mrgn.length, 'val' => mrgn, 'type'=>'bytes' },
  # TRIG
  { 'name' => 'TRIG', 'length'=>trig.length, 'val' => trig, 'type'=>'bytes' },
  # Mission briefing section
  { 'name'=>'MBRF', 'length'=>0, 'val'=>'', 'type'=>'chars' },
  # Connect scenario properties to strings (pointing to null strings in STR
  { 'name'=>'SPRP', 'length'=>4, 'val'=>[0,0], 'type'=>'int' },
  # Force/team specs
  { 'name'=>'FORC', 'length'=>20, 'val'=>forc, 'type'=>'bytes' },
  # Paths to WAV files used
  { 'name'=>'WAV',  'length'=>wav.length*2, 'val'=>wav, 'type'=>'int' },
  # UNIS not used
  # UPGS not used
  # TECS not used
  # String of switch names
  { 'name'=>'SWNM', 'length'=>swnm.length*4, 'val'=>swnm, 'type'=>'long' },
  # Colors per player
  { 'name'=>'COLR', 'length'=>colr.length, 'val'=>colr, 'type'=>'bytes' },
  # PUPx overrides UPGR for BW, setting all to 1 to let defaults take over
  { 'name'=>'PUPx', 'length'=>pupx.length, 'val'=>pupx, 'type'=>'chars' },
  # PTEx overrides PTEC for BW, setting all to 1 to let defaults take over
  { 'name'=>'PTEx', 'length'=>ptex.length, 'val'=>ptex, 'type'=>'chars' },
  # UNIx overrides UNIS for BW, setting all to 1 to let defaults take over
  { 'name'=>'UNIx', 'length'=>unix.length, 'val'=>unix, 'type'=>'chars' },
  # UPGx overrides UPGS for BW, setting all to 1 to let defaults take over
  { 'name'=>'UPGx', 'length'=>upgx.length, 'val'=>upgx, 'type'=>'chars' },
  # TECx overrides TECS for BW, setting all to 1 to let defaults take over
  { 'name'=>'TECx', 'length'=>tecx.length, 'val'=>tecx, 'type'=>'chars' },

]

def parse sections
  sections.each do |sec|
    create_section sec['name'], sec['length'], sec['val'], sec['type']
  end
  File.open(@output_name, 'wb') { |f|
    f.write @b_string
  }
end


def create_section name, length, val, type
  name << ' ' while name.length < 4
  length = [ length ].pack( @types['long'] )
  if val.kind_of?(Array)
    val = val.pack( @types[type] * val.length )
  elsif type != 'chars'
    val = [ val ].pack( @types[type] )
  end
  
  @b_string << name + length + val 
end

def s_to_hexstring s
  s.unpack('U'*s.length).collect {|x| x.to_s 16}.join
end

parse(sections)
