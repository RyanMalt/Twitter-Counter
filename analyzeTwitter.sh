#!/bin/bash

VALIDQUERY=false

while getopts ":a:o:q:t:vh" opt; do
    case $opt in
        q)
            VALIDQUERY=true
            ;;
        h)
            echo "Options: -a [OATH FILE] -o [OUTPUT] -t [RAW_OUTPUT] -q [QUERY] -v -h"
            exit 1
            ;;
    esac
done

if ( ! $VALIDQUERY ); then
    echo "Error: Program requires valid query. ex) -q #ryansproject";
    exit 0;

else
    OPTIND=1;
fi

query="0"
pythOath="oauth.txt"
outputFile="output.txt"
twitterFile="tweets.txt"
inputFile="raw_"
VERBOSE="0"

while getopts ":a:o:q:t:v" opt; do
    case $opt in
        a)
            pythOath=$OPTARG
            ;;
        o)  
            outputFile=$OPTARG
            ;;
        q)  
            query=$OPTARG
            ;;
        v)  
            VERBOSE="1"
            ;;
        t)
            twitterFile=$OPTARG
            ;;
        :)
            echo "Option -$OPTARG requires an argument."
            exit 1
            ;;
        \?)
            echo "Invalid option: -$OPTARG requires an argument."
            exit 1
            ;;
    esac
done

inputFile=($inputFile$twitterFile)

./twitterScript.py $pythOath $query $twitterFile $VERBOSE

./Tweetalyzer.out $inputFile $outputFile

echo "Processing complete! Your processed data is stored in $outputFile."
echo "Please wait fifteen minutes before attempting another request."
echo "Current time is: $(date +%R)"

