module carter_wegman_module

use, intrinsic :: iso_fortran_env, only: int64

implicit none

type carter_wegman_hash
  integer(kind=int64) :: a
  integer(kind=int64) :: b
  integer(kind=int64) :: p
  integer(kind=int64) :: n
  integer(kind=int64) :: k
end type carter_wegman_hash
end module

subroutine carter_wegman_init(hash)
  use carter_wegman_module

  implicit none

  type(carter_wegman_hash), intent(inout) :: hash

  hash%a = 0
  hash%b = 0
  hash%p = 0
  hash%n = 0
  hash%k = 0
end subroutine

subroutine carter_wegman_set(hash, n_, k_)
  use carter_wegman_module
  use, intrinsic :: iso_fortran_env, only: real64

  implicit none

  type(carter_wegman_hash), intent(inout) :: hash
  integer(kind=int64), intent(in) :: n_
  integer(kind=int64), intent(in) :: k_

  integer(kind=int64) :: candidate
  integer(kind=int64) :: i
  real(kind=real64) :: r
  logical :: is_prime

  print*,"SET n_:",n_
  print*,"SET k_:",k_

  if (n_ /= hash%n) then
    is_prime = .false.
    if (n_ <= 1) then
      hash%p = 2
      is_prime = .true.
    end if

    candidate = n_
    do while (.not. is_prime)
      i = 2
      is_prime = .true.
      candidate = candidate + 1
      do while (i * i <= candidate)
        if (modulo(candidate, i) == 0) then
          is_prime = .false.
        end if
        i = i + 1
      end do
      hash%p = candidate
    end do
  end if

  hash%n = n_
  hash%k = k_

  call random_number(r)
  hash%a = 1 + floor(r * hash%p)

  call random_number(r)
  hash%b = floor(r * (hash%p + 1))
end subroutine


subroutine carter_wegman_h(hash, input, output)
  use carter_wegman_module

  implicit none

  type(carter_wegman_hash), intent(inout) :: hash
  integer(kind=int64), intent(in) :: input
  integer(kind=int64), intent(out) :: output

  output = modulo(modulo(hash%a * input + hash%b, hash%p), hash%k)
end subroutine
