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

pub fn run_part_1(file_path: String) -> Result<(),Box<dyn Error>>{
    let contents = fs::read_to_string(file_path)?;

    // create a vector to hold our data
    let mut list_1: Vec<i32> = Vec::new();
    let mut list_2: Vec<i32> = Vec::new();

    // Convert text input into two int vectors
    for line in contents.lines(){
        // split the string into two strings: list1_item and list2_item
        let parts_string = line.split_whitespace();
        let parts_vec: Vec<&str> = parts_string.collect();

        let part_1_int = parts_vec[0].parse::<i32>().unwrap();
        let part_2_int = parts_vec[1].parse::<i32>().unwrap();

        list_1.push(part_1_int);
        list_2.push(part_2_int);
    }
        // println!("{part_1_int} , {part_2_int}");
        // println!( " " );
        // convert each item to a int
        // list1_item.parse::<i32>().unwrap();
        // list2_item.parse::<i32>().unwrap();

        // add to a vector

    // Sort each of the lists: small to large
    list_1.sort();
    list_2.sort();


    // part 1
    println!("-- Part 1 --");
    let list_length = list_1.len();
    let mut sum_p1: u64 = 0;
    for i in 0..list_length{

        let dif  = list_1[i] - list_2[i];
        let dif_abs  = dif.abs();
        let dif_abs_u64 = dif_abs as u64;
        sum_p1 = sum_p1 + dif_abs_u64;

    }
    println!("Results Part 1: {sum_p1}");

    Ok(())
}

pub fn run_part_2(file_path: String) -> Result<(),Box<dyn Error>>{
    let contents = fs::read_to_string(file_path)?;

    // create a vector to hold our data
    let mut list_1: Vec<i32> = Vec::new();
    let mut list_2: Vec<i32> = Vec::new();

    // Convert text input into two int vectors
    for line in contents.lines(){
        // split the string into two strings: list1_item and list2_item
        let parts_string = line.split_whitespace();
        let parts_vec: Vec<&str> = parts_string.collect();

        let part_1_int = parts_vec[0].parse::<i32>().unwrap();
        let part_2_int = parts_vec[1].parse::<i32>().unwrap();

        list_1.push(part_1_int);
        list_2.push(part_2_int);
    }
        // println!("{part_1_int} , {part_2_int}");
        // println!( " " );
        // convert each item to a int
        // list1_item.parse::<i32>().unwrap();
        // list2_item.parse::<i32>().unwrap();

        // add to a vector

    // Sort each of the lists: small to large
    list_1.sort();
    list_2.sort();
    let list_length = list_1.len();
    // Part 2
    println!("-- Part 2 --");
    let mut sum_p2: u64 = 0;
    // for each item in list_1
    for i in 0..list_length{
        let item = list_1[i];

        // count the number of times it appears in list 2
        let count = list_2.iter().filter(|&n| *n == item).count();
        // println!("value: {item}    count: {count}");

        let item_uSize = item as usize;
        // multiple the number of items it appears by the item values
        let item_result = count * item_uSize;

        // println!("result = {item_result}");
        // sum all the results
        sum_p2 = sum_p2 + (item_result as u64);
    }

    println!("Results Part 2: {sum_p2}");
    Ok(())
}

pub fn search<'a>(query: &str, contents: &'a str) -> Vec<&'a str> {
    let mut results = Vec::new();

    for line in contents.lines(){
        if line.contains(query){
            results.push(line);
        }
    }
    results
}

#[cfg(test)]
mod tests{
    use super::*;

    #[test]
    fn one_result(){
        let query = "duct";
        let contents = "\
Rust:
safe, fast, productive
Pick three.";
        assert_eq!(vec!["safe, fast, productive"], search(query, contents));
    }
}