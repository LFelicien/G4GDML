./load_gdml xenon.gdml &

pid=$!
sleep 70m
kill -KILL $pid
SRC='lunit="cm" name="STracker" x="3" y="3" z="3"'
DST='lunit="cm" name="STracker" x="6" y="6" z="6"'

sed -i "s/$SRC/$DST/g" xenon.gdml
./load_gdml xenon.gdml &

pid=$!
sleep 70m 
kill -KILL $pid
SRC='lunit="cm" name="STracker" x="6" y="6" z="6"'
DST='lunit="cm" name="STracker" x="10" y="10" z="6"'

sed -i "s/$SRC/$DST/g" xenon.gdml
./load_gdml xenon.gdml &

pid=$!
sleep 70m 
kill -KILL $pid

SRC='lunit="cm" name="STracker" x="10" y="10" z="6"'
DST='lunit="cm" name="STracker" x="20" y="20" z="6"'

sed -i "s/$SRC/$DST/g" xenon.gdml
./load_gdml xenon.gdml &

pid=$!
sleep 70m 
kill -KILL $pid

SRC='lunit="cm" name="STracker" x="20" y="20" z="6"'
DST='lunit="cm" name="STracker" x="25" y="25" z="8"'

sed -i "s/$SRC/$DST/g" xenon.gdml
./load_gdml xenon.gdml &

pid=$!
sleep 70m 
kill -KILL $pid

SRC=$DST
DST='lunit="cm" name="STracker" x="20" y="20" z="16"'

sed -i "s/$SRC/$DST/g" xenon.gdml
./load_gdml xenon.gdml &

pid=$!
sleep 70m 
kill -KILL $pid
SRC=$DST
DST='lunit="cm" name="STracker" x="2" y="2" z="2"'

sed -i "s/$SRC/$DST/g" xenon.gdml
./load_gdml xenon.gdml &

pid=$!
sleep 70m 
kill -KILL $pid
