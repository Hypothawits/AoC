use std::error::Error;
use std::process;
use std::env;
use std::fs;

use day_01::Config;

fn main() {
    println!("--- Day 2 ---");

    let args: Vec<String> = env::args().collect();
    let config = Config::build(&args).unwrap_or_else(|err| {
        println!("problem parsing arguments: {err}");
        process::exit(1);
    });

    // destructure input args here so I can pass to both part 1 and 2 functions
    // to avoid the "use of moved value".

    let file_path = config.file_path;

    if config.part == "1" {
        println!("Run Part 1 with {}", file_path);

        if let Err(e) = day_01::run_part_1(file_path){
            println!("Application Error: {e}");
            process::exit(1);
        }

    }else if config.part == "2" {
        println!("Run Part 2 with {}", file_path);

        if let Err(e) = day_01::run_part_2(file_path){
            println!("Application Error: {e}");
            process::exit(1);
        }

    }else if config.part == "3" {

        println!("Run both part 1 & 2 with {}", file_path);

        let file_path_2 = file_path.clone();

        if let Err(e) = day_01::run_part_1(file_path){
            println!("Application Error: {e}");
            process::exit(1);
        }

        if let Err(e) = day_01::run_part_2(file_path_2){
            println!("Application Error: {e}");
            process::exit(1);
        }

    }else {
        println!("Not Part Selected! Valid parts 1 or 2");
        process::exit(1);
    }

    // if let Err(e) = day_01::run(config){
    //     println!("Application Error: {e}");
    //     process::exit(1);
    // }

}
