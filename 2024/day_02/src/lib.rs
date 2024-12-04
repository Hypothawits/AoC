use std::error::Error;
use std::{fs, result};
pub struct Config {
    pub part: String,
    pub file_path: String,
}

impl Config {
    pub fn build(args: &[String]) -> Result<Config, &'static str> {
        if args.len() < 3 {
            return Err("not enough arguments");
        }
        let part = args[1].clone();
        let file_path = args[2].clone();

        Ok(Config { part, file_path })
    }
}

pub struct Report{
    pub report: Vec<u32>,
}

// impl Report {
//     pub fn build ()
// }

pub fn run_part_1(file_path: String) -> Result<(),Box<dyn Error>>{
    let contents = fs::read_to_string(file_path)?;

    // create a vector to hold our data
    // let mut report_line = Vec::new();
    let mut report_card = Vec::new();
    //let mut list_2: Vec<i32> = Vec::new();

    // Convert text input into two int vectors
    for line in contents.lines(){
        // split the string into two strings: list1_item and list2_item
        let parts_string = line.split_whitespace();
        let parts_vec: Vec<&str> = parts_string.collect();

        let mut report_line = Vec::new();
        for part in parts_vec{
            let part_int = part.parse::<u32>().unwrap();
            report_line.push(part_int);
        }
        report_card.push(report_line);
    }

    // part 1
    println!("-- Part 1 --");

    // Print the input data
    // let report_slice = report_card.iter();
    // for report in report_slice{
    //     for val in report{
    //         print!("{val} ");
    //     }
    //     println!("");
    // }

    //Check if the report is safe
    // check 1: levels are either all increasion or all decreasing.
    // check 2: any two levels differ by at least 1 and at most 3.

    // Create a difference card

    // let mut difference_card = Vec::new();
    //let mut list_2: Vec<i32> = Vec::new();
    let report_slice = report_card.iter();
    let mut difference_card = Vec::new();

    for report in report_slice{
        // I want to get 2 consecitive values each step
        // can use Zip from standard library
        // or windows. I will use windows

        // windows object is iterable
        let iter = report.windows(2);

        let mut difference_line = Vec::new();

        for pair in iter{
            let difference = (pair[0] as i64) - (pair[1] as i64);
            difference_line.push(difference);

            // println!("{} {}",pair[0], pair[1]);
        }
        difference_card.push(difference_line);
    }

    // println!("Results Part 1: diference!");
    // Print the difference  data
    
    let difference_slice = difference_card.iter();
    let mut sum = difference_slice.len();

    for difference in difference_slice{
        // for val in difference{
        //     print!("{val} ");
        // }

        let mut fail = 0;

        // check for no change
        if difference.iter().any(|&i| i == 0){
            // print!("Fail: no change");
            fail = 1;
        }

        // check if all rise or fall
        if difference.iter().all(|&i| i >=0){
            // println!("all positive");
        }
        else if difference.iter().all(|&i| i <0){
            // println!("all negative");
        }
        else {
            // print!("Fail: continuity check");
            fail = 1;
        }

        // check if change greater than 3
        if difference.iter().any(|&i| (i > 3) || (i < -3)){
            // print!("Fail: Change to great");
            fail = 1;
        }

        sum = sum - fail;

        // println!("");
    }

    println!("Results Part 1: {sum}");

    Ok(())
}

pub fn run_part_2(file_path: String) -> Result<(),Box<dyn Error>>{
    // Part 2
    println!("-- Part 2 --");
    let contents = fs::read_to_string(file_path)?;

    // create a vector to hold our data
    // let mut report_line = Vec::new();
    let mut report_card = Vec::new();
    //let mut list_2: Vec<i32> = Vec::new();

    // Convert text input into two int vectors
    for line in contents.lines(){
        // split the string into two strings: list1_item and list2_item
        let parts_string = line.split_whitespace();
        let parts_vec: Vec<&str> = parts_string.collect();

        let mut report_line = Vec::new();
        for part in parts_vec{
            let part_int = part.parse::<u32>().unwrap();
            report_line.push(part_int);
        }
        report_card.push(report_line);
    }
    //Check if the report is safe
    // check 1: levels are either all increasion or all decreasing.
    // check 2: any two levels differ by at least 1 and at most 3.

    // Create a difference card

    // let mut difference_card = Vec::new();
    //let mut list_2: Vec<i32> = Vec::new();
    let report_slice = report_card.iter();
    let mut difference_card = Vec::new();

    for report in report_slice{
        // I want to get 2 consecitive values each step
        // can use Zip from standard library
        // or windows. I will use windows

        // windows object is iterable
        let iter = report.windows(2);

        let mut difference_line = Vec::new();

        for pair in iter{
            let difference = (pair[1] as i64) - (pair[0] as i64);
            difference_line.push(difference);

            // println!("{} {}",pair[0], pair[1]);
        }
        difference_card.push(difference_line);
    }

    // println!("Results Part 1: diference!");
    // Print the difference  data

    let difference_slice = difference_card.iter();
    let mut sum = difference_slice.len();

    for difference in difference_slice{
        for val in difference{
            print!("{val} ");
        }

        let mut fail = 0;

        // check for no change
        if difference.iter().any(|&i| i == 0){
            // print!("Fail: no change");
            fail = 1;
        }

        // check if all rise or fall
        if difference.iter().all(|&i| i >=0){
            // println!("all positive");
        }
        else if difference.iter().all(|&i| i <0){
            // println!("all negative");
        }
        else {
            // print!("Fail: continuity check");
            fail = 1;
        }

        // check if change greater than 3
        if difference.iter().any(|&i| (i > 3) || (i < -3)){
            // print!("Fail: Change to great");
            fail = 1;
        }

        sum = sum - fail;

        println!("");
    }
    println!("Results Part 2: Empty");
    Ok(())
}

//Check if the report is safe
// check 1: levels are either all increasion or all decreasing.
// check 2: any two levels differ by at least 1 and at most 3.

// if the error is that the jump it too much, that error cannot be fixed by removing
// a value. (assume that it passes the all incr or all decr)

// errors from direction change can be fixed.

pub fn search<'a>(query: &str, contents: &'a str) -> Vec<&'a str> {
    let mut results = Vec::new();

    for line in contents.lines(){
        if line.contains(query){
            results.push(line);
        }
    }
    results
}
