use std::error::Error;
use std::{fs, result};
use regex::Regex;

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
    // let mut cmd_line = Vec::new();
    //let mut list_2: Vec<i32> = Vec::new();

    // Convert text input into two int vectors
    let mut sum: u64 = 0;

    for line in contents.lines(){
        // split the string into two strings: list1_item and list2_item
        println!("{line}");

        let find_mul = Regex::new(r"mul\(\d+,\d+\)").unwrap();
        // let find_mul = Regex::new(r"mul").unwrap();
        let mut reg_results =Vec::new();

        for cap in find_mul.captures_iter(line){
            reg_results.push(cap.get(0).unwrap().as_str());

        }

        for result in reg_results{
            println!("{result}");
            let find_num = Regex::new(r"\d+").unwrap();

            let mut local_sum: u64 = 1;
            for cap in find_num.captures_iter(result){
                let numb = cap.get(0).unwrap().as_str().parse::<u64>().unwrap();

                // print!("number: {numb} ");
                local_sum = local_sum*numb;
            }
            println!("");
            sum = sum + local_sum;
        }
    }

    // part 1
    println!("-- Part 1 --");

    println!("Results Part 1: {sum}");

    Ok(())
}

pub fn run_part_2(file_path: String) -> Result<(),Box<dyn Error>>{
    // Part 2
    let contents = fs::read_to_string(file_path)?;

    // create a vector to hold our data
    // let mut report_line = Vec::new();
    // let mut cmd_line = Vec::new();
    //let mut list_2: Vec<i32> = Vec::new();

    // Convert text input into two int vectors
    let mut sum: u64 = 0;

    let mut do_mult = true;
    for line in contents.lines(){
        // split the string into two strings: list1_item and list2_item
        println!("{line}");

        let find_mul = Regex::new(r"(mul\(\d+,\d+\)|don't|do)").unwrap();
        // let find_mul = Regex::new(r"mul").unwrap();
        let mut reg_results =Vec::new();

        for cap in find_mul.captures_iter(line){
            reg_results.push(cap.get(0).unwrap().as_str());

        }

        for result in reg_results{
            // println!("sum: {sum}");
            println!("{result}");
            let find_num = Regex::new(r"\d+").unwrap();
            let mut local_sum: u64 = 1;

            if result == "don't" {
                do_mult = false;
                // println!("dont: {result}");
            }else if result == "do" {
                do_mult = true;
                // println!("do: {result}");
            }else {
                if do_mult{
                    // println!("do: {result}");
                    for cap in find_num.captures_iter(result){

                        let numb = cap.get(0).unwrap().as_str().parse::<u64>().unwrap();

                        // print!("number: {numb} ");
                        local_sum = local_sum*numb;
                    }
                    // println!("");
                    sum = sum + local_sum;
                } else {
                    // println!("dont: {result}");
                }
            }
        }
    }

    println!("-- Part 2 --");

    println!("Results Part 2: {sum}");
    // println!("Result correct? {}", sum == 59097164);

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
