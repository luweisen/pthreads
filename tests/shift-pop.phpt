--TEST--
Test shift and pop
--DESCRIPTION--
This test verifies that shift and pop functionality are working
--FILE--
<?php
class S extends Threaded {
	public function run(){}
}
$s = new S();
$s[] = "help";
var_dump($s);
var_dump($s->shift());
var_dump($s);
$s[] = "next";
var_dump($s);
var_dump($s->pop());
var_dump($s);
while (@$i++<100)
    $s[$i]=$i;
var_dump($s);
while (($next = $s->pop())) {
    var_dump($next);
}
?>
--EXPECTF--
object(S)#%d (1) {
  [0]=>
  string(4) "help"
}
string(4) "help"
object(S)#%d (0) {
}
object(S)#%d (1) {
  [1]=>
  string(4) "next"
}
string(4) "next"
object(S)#%d (0) {
}
object(S)#%d (100) {
  [1]=>
  int(1)
  [2]=>
  int(2)
  [3]=>
  int(3)
  [4]=>
  int(4)
  [5]=>
  int(5)
  [6]=>
  int(6)
  [7]=>
  int(7)
  [8]=>
  int(8)
  [9]=>
  int(9)
  [10]=>
  int(10)
  [11]=>
  int(11)
  [12]=>
  int(12)
  [13]=>
  int(13)
  [14]=>
  int(14)
  [15]=>
  int(15)
  [16]=>
  int(16)
  [17]=>
  int(17)
  [18]=>
  int(18)
  [19]=>
  int(19)
  [20]=>
  int(20)
  [21]=>
  int(21)
  [22]=>
  int(22)
  [23]=>
  int(23)
  [24]=>
  int(24)
  [25]=>
  int(25)
  [26]=>
  int(26)
  [27]=>
  int(27)
  [28]=>
  int(28)
  [29]=>
  int(29)
  [30]=>
  int(30)
  [31]=>
  int(31)
  [32]=>
  int(32)
  [33]=>
  int(33)
  [34]=>
  int(34)
  [35]=>
  int(35)
  [36]=>
  int(36)
  [37]=>
  int(37)
  [38]=>
  int(38)
  [39]=>
  int(39)
  [40]=>
  int(40)
  [41]=>
  int(41)
  [42]=>
  int(42)
  [43]=>
  int(43)
  [44]=>
  int(44)
  [45]=>
  int(45)
  [46]=>
  int(46)
  [47]=>
  int(47)
  [48]=>
  int(48)
  [49]=>
  int(49)
  [50]=>
  int(50)
  [51]=>
  int(51)
  [52]=>
  int(52)
  [53]=>
  int(53)
  [54]=>
  int(54)
  [55]=>
  int(55)
  [56]=>
  int(56)
  [57]=>
  int(57)
  [58]=>
  int(58)
  [59]=>
  int(59)
  [60]=>
  int(60)
  [61]=>
  int(61)
  [62]=>
  int(62)
  [63]=>
  int(63)
  [64]=>
  int(64)
  [65]=>
  int(65)
  [66]=>
  int(66)
  [67]=>
  int(67)
  [68]=>
  int(68)
  [69]=>
  int(69)
  [70]=>
  int(70)
  [71]=>
  int(71)
  [72]=>
  int(72)
  [73]=>
  int(73)
  [74]=>
  int(74)
  [75]=>
  int(75)
  [76]=>
  int(76)
  [77]=>
  int(77)
  [78]=>
  int(78)
  [79]=>
  int(79)
  [80]=>
  int(80)
  [81]=>
  int(81)
  [82]=>
  int(82)
  [83]=>
  int(83)
  [84]=>
  int(84)
  [85]=>
  int(85)
  [86]=>
  int(86)
  [87]=>
  int(87)
  [88]=>
  int(88)
  [89]=>
  int(89)
  [90]=>
  int(90)
  [91]=>
  int(91)
  [92]=>
  int(92)
  [93]=>
  int(93)
  [94]=>
  int(94)
  [95]=>
  int(95)
  [96]=>
  int(96)
  [97]=>
  int(97)
  [98]=>
  int(98)
  [99]=>
  int(99)
  [100]=>
  int(100)
}
int(100)
int(99)
int(98)
int(97)
int(96)
int(95)
int(94)
int(93)
int(92)
int(91)
int(90)
int(89)
int(88)
int(87)
int(86)
int(85)
int(84)
int(83)
int(82)
int(81)
int(80)
int(79)
int(78)
int(77)
int(76)
int(75)
int(74)
int(73)
int(72)
int(71)
int(70)
int(69)
int(68)
int(67)
int(66)
int(65)
int(64)
int(63)
int(62)
int(61)
int(60)
int(59)
int(58)
int(57)
int(56)
int(55)
int(54)
int(53)
int(52)
int(51)
int(50)
int(49)
int(48)
int(47)
int(46)
int(45)
int(44)
int(43)
int(42)
int(41)
int(40)
int(39)
int(38)
int(37)
int(36)
int(35)
int(34)
int(33)
int(32)
int(31)
int(30)
int(29)
int(28)
int(27)
int(26)
int(25)
int(24)
int(23)
int(22)
int(21)
int(20)
int(19)
int(18)
int(17)
int(16)
int(15)
int(14)
int(13)
int(12)
int(11)
int(10)
int(9)
int(8)
int(7)
int(6)
int(5)
int(4)
int(3)
int(2)
int(1)
