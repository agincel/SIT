-module(watcher).
-compile([setup/0]).

% Adam Gincel and Alex Massenzio
% watcher.erl
% We pledge our honor that we have abided by the Stevens Honor System.


setup() ->
    {ok, [ N ]} = io:fread("How many sensors?> ", "~d") ,
    if N =< 1 ->
      io:fwrite("setup: range must be at least 2~n", []) ;
    true ->
        Num_watchers = 1 + ((N-1) div 10) ,
        setup_loop(N, Num_watchers, N) 
    end.

setup_loop(0, _Num_watchers, _) -> % Base case. Setup has generated all watchers.
    io:fwrite("Setup is complete.~n");
setup_loop(N, Num_watchers, OriginalN) -> % Create N / Watchers, each of which spawns up to ten sensors.
    if
        (N-10) =< 0 -> % last one does remainder of ten, ie with 93 sensors the last watcher spawns the last 3
            spawn(watcher, create, [OriginalN - N, N]),
            setup_loop(0, Num_watchers - 1, OriginalN);
        true -> % otherwise, spawn a watcher that will spawn ten sensors
            spawn(watcher, create, [OriginalN - N, 10]),
            setup_loop(N-10, Num_watchers - 1, OriginalN)
    end.


create(StartingID, HowManySensors) -> %this creates a watcher; it runs spawn_sensors_loop to populate its initial sensorList, then prints that and starts listening for messages from them.
     SensorList = spawn_sensors_loop(HowManySensors, self(), StartingID, []),
     io:fwrite("I started at ID ~p and started ~p Sensors. ~nMy Sensors are ~p~n~n", [StartingID, HowManySensors, SensorList]),
     listen_loop(StartingID, SensorList).

spawn_sensors_loop(0, _WatcherPid, _CurrentID, SensorList) -> % return assembled SensorList
    SensorList;
spawn_sensors_loop(HowManySensors, WatcherPid, CurrentID, SensorList) -> % spawn a sensor, add its ID and Pid to SensorList and loop tail-recursively
    {Pid, _ } = spawn_monitor(sensor, sense, [WatcherPid, CurrentID]),
    spawn_sensors_loop(HowManySensors - 1, WatcherPid, CurrentID + 1, SensorList ++ [{CurrentID, Pid}]).



listen_loop(StartingID, SensorList) -> % this listens for Measurements or for anomalous_reading
    receive
        {ID, anomalous_reading} -> % sensor died, remove its tuple from SensorList and spawn a new one with its ID.
            io:fwrite("Sensor ~p died with ~p~n", [ID, anomalous_reading]),
            NewList = lists:keydelete(ID, 1, SensorList),
            {NewPid, _} = spawn_monitor(sensor, sense, [self(), ID]),
            NewNewList = NewList ++ [{ID, NewPid}], % ugh, this language
            io:fwrite("Watcher ~p's new sensor list is ~p~n", [StartingID, NewNewList]),
            listen_loop(StartingID, NewNewList);
        {ID, Measurement} -> % received Measurement to Print
            io:fwrite("Sensor ~p measured ~p~n", [ID, Measurement]),
            listen_loop(StartingID, SensorList)
        end.





