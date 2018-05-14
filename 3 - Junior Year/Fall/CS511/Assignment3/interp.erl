-module(interp).
-export([scanAndParse/1,runFile/1,runStr/1,scanAndParseString/1]).
-include("types.hrl").

% Adam Gincel and Alex Massenzio
% interp.erl
% I pledge my honor that I have abided by the Stevens Honor System.


loop(InFile,Acc) ->
    case io:request(InFile,{get_until,prompt,lexer,token,[1]}) of
        {ok,Token,_EndLine} ->
            loop(InFile,Acc ++ [Token]);
        {error,token} ->
            exit(scanning_error);
        {eof,_} ->
            Acc
    end.

scanAndParse(FileName) ->
    {ok, InFile} = file:open(FileName, [read]),
    Acc = loop(InFile,[]),
    file:close(InFile),
    {Result, AST} = parser:parse(Acc),
    case Result of 
	ok -> AST;
	_ -> io:format("Parse error~n")
    end.


-spec runFile(string()) -> valType().
runFile(FileName) ->
    valueOf(scanAndParse(FileName),env:new()).

scanAndParseString(String) ->
    {_ResultL, TKs, _L} = lexer:string(String),
    parser:parse(TKs).

-spec runStr(string()) -> valType().
runStr(String) ->
    {Result, AST} = scanAndParseString(String),
    case Result  of 
    	ok -> valueOf(AST,env:new());
    	_ -> io:format("Parse error~n")
    end.


-spec numVal2Num(numValType()) -> integer().
numVal2Num({num, N}) ->
    N.

-spec boolVal2Bool(boolValType()) -> boolean().
boolVal2Bool({bool, B}) ->
    B.

-spec valueOf(expType(),envType()) -> valType().
valueOf({numExp, {num,_, N}}, _Env) ->
    {num, N};
valueOf({boolExp, {bool, _, B}}, _Env) ->
    {bool, B};
valueOf({procExp, {id, _, I}, Expression}, Env) ->
    {proc, I, Expression, Env};
valueOf({proc, ID, Expression, _OLDENV}, Env) ->
    {proc, ID, Expression, Env};
valueOf({idExp, {id,_,I}}, Env) ->
    env:lookup(Env, I);
valueOf({diffExp, E1, E2}, Env) ->
    {num, numVal2Num(valueOf(E1, Env)) - numVal2Num(valueOf(E2, Env))};
valueOf({plusExp, E1, E2}, Env) ->
    {num, numVal2Num(valueOf(E1, Env)) + numVal2Num(valueOf(E2, Env))};
valueOf({isZeroExp, E}, Env) ->
    {bool, numVal2Num(valueOf(E, Env)) == 0};
valueOf({ifThenElseExp, E1, E2, E3}, Env) ->
    case boolVal2Bool(valueOf(E1, Env)) of
        true -> valueOf(E2, Env);
        false -> valueOf(E3, Env) end;
valueOf({letExp, {id,_,I}, E1, E2}, Env) ->
    valueOf(E2, env:add(Env, I, valueOf(E1, Env)));
valueOf({appExp, ID, E2}, Env) ->
   {proc, V, _Exp, _Env2} = valueOf(ID, Env),
   {proc, _, RetExp, NewEnv} = valueOf(valueOf(ID, Env), env:add(Env, V, valueOf(E2, Env))),
   valueOf(RetExp, NewEnv).

