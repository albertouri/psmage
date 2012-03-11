#!/usr/bin/ruby

@types = {
  'chars' => 'A',  # not changed
  'bytes'  => 'C',  # one byte
  'int'   => 'S',  # small-endian int, 2 bytes
  'long'  => 'L'   # small-endian long, 4 bytes
}
@b_string = ''
vcod = (File.open('vcod.bin', 'rb')).read
puni = []; 5700.times { |x| puni << 1 }
unit = []; #214 (int) is starting location
isom = []; # (width/2 + 1) * (height+1) * 4, 16 int
tile = []; # w*h * 2 (because ints), one int per tile

width = 128
height = 128


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
  { 'name'=> 'VCOD', 'length'=> 1040, 'val'=> vcod,   'type'=> 'chars' },
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
  # Player unit restrictions, all 1s for normal defaults (5700 times)
  { 'name'=> 'PUNI', 'length'=>5700,   'val'=> puni, 'type'=>'bytes' },
  # Flags and stats of each unit on the map (only starting locations for this)
  { 'name'=> 'UNIT', 'length'=>72,     'val'=> unit, 'type'=>'chars' },
  # Tile map of level's terrain 
  { 'name'=> 'TILE', 'length'=>tile.length * 2, 'val'=> tile, 'type'=>'int' }

]

def parse sections
  sections.each do |sec|
    create_section sec['name'], sec['length'], sec['val'], sec['type']
  end
  p @b_string
  File.open('output.chk', 'wb') { |f|
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
