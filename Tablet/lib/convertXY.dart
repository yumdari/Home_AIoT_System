import 'dart:math';

class ConvertXY {
  int x;
  int y;
  ConvertXY(this.x, this.y);
}

class lamc_parameter {
  double Re = 0; /* 사용할 지구반경 [ km ]      */
  double grid = 0; /* 격자간격        [ km ]      */
  double slat1 = 0; /* 표준위도        [degree]    */
  double slat2 = 0; /* 표준위도        [degree]    */
  double olon = 0; /* 기준점의 경도   [degree]    */
  double olat = 0; /* 기준점의 위도   [degree]    */
  double xo = 0; /* 기준점의 X 좌표  [격자거리]  */
  double yo = 0; /* 기준점의 Y 좌표  [격자거리]  */
  int first = 0; /* 시작여부 (0 = 시작)         */
}

ConvertXY changelaluMap(double longitude, double latitude) {
  int NX = 149; /* X 축 격자점 수 */
  int NY = 253; /* Y 축 격자점 수 */
  double? PI, DEGRAD, RADDEG;
  double? re, olon, olat, sn, sf, ro;
  double slat1, slat2, alon, alat, xn, yn, ra, theta;
  lamc_parameter map = lamc_parameter();
  map.Re = 6371.00877; // 지도반경
  map.grid = 5.0; // 격자간격 (km)
  map.slat1 = 30.0; // 표준위도 1
  map.slat2 = 60.0; // 표준위도 2
  map.olon = 126.0; // 기준점 경도
  map.olat = 38.0; // 기준점 위도
  map.xo = 210 / map.grid; // 기준점 X 좌표
  map.yo = 675 / map.grid; // 기준점 Y 좌표
  map.first = 0;
  if ((map).first == 0) {
    // PI = asin(1.0) * 2.0;
    PI = 3.1415926535897931;
    DEGRAD = PI / 180.0;
    RADDEG = 180.0 / PI;
    re = map.Re / map.grid;
    slat1 = map.slat1 * DEGRAD;
    slat2 = map.slat2 * DEGRAD;
    olon = map.olon * DEGRAD;
    olat = map.olat * DEGRAD;
    sn = tan(PI * 0.25 + slat2 * 0.5) / tan(PI * 0.25 + slat1 * 0.5);
    sn = log(cos(slat1) / cos(slat2)) / log(sn);
    sf = tan(PI * 0.25 + slat1 * 0.5);
    sf = pow(sf, sn) * cos(slat1) / sn;
    ro = tan(PI * 0.25 + olat * 0.5);
    ro = re * sf / pow(ro, sn);
    map.first = 1;
  }
  ra = tan(PI * 0.25 + latitude * DEGRAD * 0.5);
  ra = re * sf / pow(ra, sn);
  theta = longitude * DEGRAD - olon;
  if (theta > PI) theta -= 2.0 * PI;
  if (theta < -PI) theta += 2.0 * PI;
  theta *= sn;

  double x = (ra * sin(theta)) + map.xo;
  double y = (ro - ra * cos(theta)) + map.yo;
  x = x + 1.5;
  y = y + 1.5;
  return ConvertXY(x.toInt(), y.toInt());
}