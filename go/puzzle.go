package main

import "fmt"

func check_line(n int, x int, array [9][9]int) int {
	for i := 0; i < 9; i++ {
		if array[x][i] == n {
			return 0
		}
	}
	return 1
}

func check_column(n int, y int, array [9][9]int) int {
	for i := 0; i < 9; i++ {
		if array[i][y] == n {
			return 0
		}
	}
	return 1
}

func check_group(n int, x int, y int, array [9][9]int) int {
	//ブロックの左上のを場所をx1, y1として置く.
	x1 := (x / 3) * 3
	y1 := (y / 3) * 3
	//そのブロックを左上から右下にかけてnと一致しているのがないか確認.一致しているのがあればfalse,なければtrue.
	for i := 0; i < 3; i++ {
		for j := 0; j < 3; j++ {
			if array[x1+i][y1+j] == n {
				return 0
			}
		}
	}
	return 1
}

func check(n int, x int, y int, array [9][9]int) int {
	return check_column(n, y, array) & check_line(n, x, array) & check_group(n, x, y, array)
}

func print_board(array [9][9]int) {

	fmt.Println(array[0][:])
	fmt.Println(array[1][:])
	fmt.Println(array[2][:])
	fmt.Println(array[3][:])
	fmt.Println(array[4][:])
	fmt.Println(array[5][:])
	fmt.Println(array[6][:])
	fmt.Println(array[7][:])
	fmt.Println(array[8][:])

	/*for i := 0; i < 9; i++ {
		for j := 0; j < 9; j++ {
			fmt.Println(array[i][j])
			if j == 8 {
				break
			}
		}
		fmt.Println("\n")
	}*/
}

func solver(n int, array [9][9]int) {
	if n == 81 {
		print_board(array)
	} else {
		//nを1から80までの再帰関数として足していく。そのため、nを９で割ることで2次元配列の行と列の指定をしている.
		x := n / 9
		y := n % 9

		if array[x][y] != 0 {
			solver(n+1, array) //再帰関数としてnを+1
		} else {
			for i := 1; i <= 9; i++ {
				if check(i, x, y, array) == 1 { //1~9まですべてがfalseの場合はそのsolverを抜け出して、一つ前のsolverのarray[x][y]＝０に代入いき、そこからfor分のiを再開させる

					array[x][y] = i    //2次元配列の任意の場所が3つの条件を満たしていたら、iを代入
					solver(n+1, array) //そしてnを+1させる、、、、memoこのやり方だと条件を満たしている値が複数あった場合、数が小さい方にしかならないのでは？
					array[x][y] = 0    //1~9まで行ってすべて違ったらこの場所を０にして戻ってやり直す
				}
			}
		}
	}
}

func main() {

	array := [9][9]int{
		{0, 0, 0, 6, 5, 0, 1, 4, 0},
		{3, 0, 0, 0, 0, 1, 0, 5, 2},
		{0, 0, 0, 0, 3, 0, 0, 9, 0},
		{0, 0, 0, 3, 0, 6, 0, 0, 0},
		{0, 9, 0, 8, 0, 0, 0, 0, 6},
		{2, 0, 8, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 1, 0},
		{0, 0, 0, 7, 4, 8, 0, 0, 0},
		{7, 2, 0, 0, 0, 0, 9, 0, 0},
	}

	var n = 0
	solver(n, array)
}
