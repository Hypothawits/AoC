#!/bin/sh

# Open file
set f [open "input.txt"]

# read whole file
set data [read $f]

# close the file
close $f

#split into lines
set text_lines [split $data "\n"]

# Print each line in file
foreach line $text_lines {
    puts $line
}

set red_cubes   12
set green_cubes 13
set blue_cubes  14

set game_number 0
set results {}

# Print each line in file
foreach file_line $text_lines {
    set game_number [expr $game_number + 1 ]
    puts "\nInput: $file_line"

    set rm_group [lindex [split $file_line ":"] 1]
    # puts "rm_group: $rm_group"

    # set subsets_of_cubes [lreplace $rm_group 0 0]
    # puts "subsets_of_cubes: $subsets_of_cubes"

    set subsets_of_cubes [split $rm_group ";"]

    set max_green 0
    set max_blue  0
    set max_red   0

    # puts "sub groups: $subsets_of_cubes"
    foreach sub_group $subsets_of_cubes {
        # puts "This sub group: $sub_group"

        set split_group [split $sub_group ","]
        foreach cube_type $split_group {
            # puts "This cube_type:$cube_type"

            set cube_type_split [split $cube_type " "]
            # puts "split: $cube_type_split"

            # Splits into 3 with first being empty. IDK why.
            set num_part [lindex $cube_type_split 1]
            # puts "Num:    $num_part"
            set colour_part [lindex $cube_type_split 2]
            # puts "Colour: $colour_part"

            if {$colour_part == "red"} {
                if {$num_part > $max_red} { set max_red $num_part }
            }
            if {$colour_part == "blue"} {
                if {$num_part > $max_blue} { set max_blue $num_part }
            }
            if {$colour_part == "green"} {
                if {$num_part > $max_green} { set max_green $num_part }
            }
        }


        # set test [scan $sub_group {%c}]
        # puts "Try to get values: $test"
    }
    puts "game number: $game_number :: max_green:$max_green, max_blue:$max_blue, max_red:$max_red"

    lappend results [list $game_number $max_red $max_green $max_blue]



}

puts $results

# game_number max_red max_green max_blue
# red_cubes   12
# green_cubes 13
# blue_cubes  14

set possible_games {}
set power_list {}

foreach game $results {
    set game_num  [lindex $game 0]
    set red_num   [lindex $game 1]
    set green_num [lindex $game 2]
    set blue_num  [lindex $game 3]

    set is_possible 1
    set power [expr $red_num * $green_num * $blue_num]
    lappend power_list $power
    # puts "game $game_num"
    # puts "$red_cubes    <  $red_num"
    # puts "$green_cubes  <  $green_num"
    # puts "$blue_cubes   <  $blue_num"

    if {$red_cubes  <  $red_num} {
        set is_possible 0
    }
    if {$green_cubes < $green_num} {
        set is_possible 0
    }
    if {$blue_cubes <  $blue_num} {
        set is_possible 0
    }

    if {$is_possible == 1} {
        lappend possible_games $game_num
    }

}

puts "possible games: $possible_games"
puts "Power games: $power_list"

set sum 0
foreach possible $possible_games {
    set sum [expr $sum + $possible]
}

puts "part one: $sum"

set sum 0
foreach power $power_list {
    set sum [expr $sum + $power]
}

puts "part two: $sum"

# 2352 too high
# set game_number [expr $game_number + 1 ]