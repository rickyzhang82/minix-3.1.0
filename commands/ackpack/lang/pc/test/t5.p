{$i1000}
program test(output);
const rcsversion='$Id: t5.p,v 1.1 2005/09/01 12:13:24 beng Exp $';
var b:false..true;
    i:integer;
    s:set of 0..999;
begin
  b:=true; if not b then writeln('error 1');
  s:=[0,100,200,300,400,500,600,700,800,900];
  for i:=0 to 999 do
    if (i in s) <> (i mod 100=0) then
      writeln('error 2');
end.
