use std::error::Error;
use std::process;
use std::env;
use std::fs;

use day_01::Config;

fn main() {
    println!("--- Day 1 ---");

    let args: Vec<String> = env::args().collect();
    let config = Config::build(&args).unwrap_or_else(|err| {
        println!("problem parsing arguments: {err}");
        process::exit(1);
    });

    if let Err(e) = day_01::run(config){
        println!("Application Error: {e}");
        process::exit(1);
    }

}
