-module(sensor).
-compile(export_all).

% Adam Gincel and Alex Massenzio
% sensor.erl
% We pledge our honor that we have abided by the Stevens Honor System.

sense(WatcherPid, ID) -> %this loops until it generates an 11, at which point it messages its watcher with anomalous_reading, then exits.
    SleepTime = rand:uniform(10000),
    timer:sleep(SleepTime),
    Measurement = rand:uniform(11),
    if
        Measurement =:= 11 ->
            WatcherPid ! {ID, anomalous_reading},
            exit(anomalous_reading);
        true ->
            WatcherPid ! {ID, Measurement}
    end,
    sense(WatcherPid, ID).