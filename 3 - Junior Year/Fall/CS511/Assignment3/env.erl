-module(env).
-compile(export_all).
-include("types.hrl").

% Adam Gincel and Alex Massenzio
% env.erl
% I pledge my honor that I have abided by the Stevens Honor System.



-spec new()-> envType().
new() ->
    dict:new().

-spec add(envType(),atom(),valType())-> envType().
add(Env,Key,Value) ->
    dict:store(Key, Value, Env).

-spec lookup(envType(),atom())-> valType().
lookup(Env,Key) -> 
   dict:fetch(Key, Env).

