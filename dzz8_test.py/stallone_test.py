from dz8.stallone import stallone
import pytest


@pytest.mark.parametrize(
    ('lst', 'sort_lst'),
    [
        ([1], [1]),
        ([1, 2, 3, 4, 5], [1, 2, 3, 4, 5]),
        ([5, 4, 3, 2, 1], [5]),
        ([1, 1, 1, 1, 1], [1, 1, 1, 1, 1]),
        ([1, 2, 1, 3, 2, 4, 3, 5], [1, 2, 3, 4, 5]),
        ([-5, -2, 0, 1, 5], [-5, -2, 0, 1, 5]),
        ([1, -2, 0, -5, 5], [1, 5]),
        ([1, 4, 2, 5, -3], [1, 4, 5]),
    ]
)
def test_stallone(lst, sort_lst):
    assert stallone(lst) == sort_lst
