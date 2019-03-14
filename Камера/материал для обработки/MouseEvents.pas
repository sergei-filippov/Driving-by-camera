// Иллюстрация обработки событий мыши
uses
  GraphABC;

var
  xn, yn, count, i, xx: integer;
  wredblock: integer := 10;
  hredblock: integer := 10;

procedure MouseDown(x, y, mb: integer);
begin
  MoveTo(x, y);
  xx := x;
  for i: integer := 0 to hredblock do 
  begin
    for j: integer := 0 to wredblock do
    begin
      setpixel(xx, y, clred);
      xx := xx + 1;
    end;
    y := y + 1;
    xx := x;
  end;
  println(x, y);
end;


begin
  setconsoleio;
  OnMouseDown := MouseDown;
end.