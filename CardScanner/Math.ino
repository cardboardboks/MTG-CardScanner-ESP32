//Calculate greatest common denominator
int gcd(int A, int B) {

  do {
    const int tmp(B);
    B = A % B;
    A = tmp;
  } while (B != 0);

  return A;
}

//Calculate least common multiple
int lcm(const int& A, const int& B) {

  int ret = A;
  ret /= gcd(A, B);
  ret *= B;
  return ret;
}