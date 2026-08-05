import argparse  # handles reading command line arguments
import random # generates random matrix value

def main():
    parser = argparse.ArgumentParser(description="Generate a random GEMM test file.")
    parser.add_argument("M", type=int) # rows of A
    parser.add_argument("K", type=int) # rows of B
    parser.add_argument("N", type=int) # cols. of B
    parser.add_argument("output_path", type=str)  #path to save the file
    parser.add_argument("--seed", type=int,default=42)  #for reproducibility
    parser.add_argument("--low", type=int, default=-10)  #smallest random value
    parser.add_argument("--high", type=int, default=10)   # largest random value
    args = parser.parse_args()

    if args.M <= 0 or args.K <=0 or args.N <=0:
        raise SystemExit("M,K,N must all be positive")

    random.seed(args.seed)  #to repeat random file everytime

    with open(args.output_path,"w") as f:

        #to write the "M,K,N"
        f.write(f"{args.M} {args.K} {args.N}\n")

        #write M rows for matrix A with K random variables
        for _in range(args.M):
            row = [random.randint(args.low, args.high) for _in range(args.K)]
            f.write(" ".join(map(str, low)) + "\n")

        # write K rows for matrix B ,each with N random variables
        for _in range(args.K):
            row = [random.randint(args.low, args.high) for _in range(args.N)]
            f.write(" ".join(map(str, low)) + "\n")    
    print(f" Wrote {args.M}* {args.K}*{args.N} test file to {args.output_path}")


    if __ name __ == "__main__":    #to run only when called directly
        main()