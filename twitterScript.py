#!/usr/bin/python

import twitter
import sys

class Interval:
    """Holds valid Twitter status id intervals"""
    lowerBound = 0
    upperBound = 0
    numStatuses = 0

approxBound = 0
maxRequests = 180
divisor = 1

MAX_TWEETS = 100
OATH = 0
QUERY = 1
OUTPUT = 2
VERBOSE = 3
OUTPUT_NAME = "raw_"


def grabTweets(api, query, Intervals, lowerBound, upperBound, 
               requestsMade, allowedQueries, tweets, verbose):
    """Recursively grabs tweets using message ids"""

    if requestsMade[0] < allowedQueries:
            statuses = api.GetSearch(query, count=100, since_id=lowerBound,
                                     max_id=upperBound, lang='en')
            requestsMade[0] = requestsMade[0] + 1

            if len(statuses) < MAX_TWEETS and len(statuses) > 0:
                    if verbose == "1":
                        print "Grabbing", len(statuses), "tweets from", lowerBound, "to", upperBound
                
                    Bound = Interval()
                    Bound.lowerBound = lowerBound
                    Bound.upperBound = upperBound
                    Bound.numStatuses = len(statuses)

                    Intervals.append(Bound)
                    tweets.extend(statuses)
            elif len(statuses) == MAX_TWEETS:
                    grabTweets(api, query, Intervals, lowerBound,
                               (upperBound + lowerBound) / 2,
                               requestsMade, allowedQueries, tweets, verbose)
                    grabTweets(api, query, Intervals, 
                               (upperBound + lowerBound) / 2, upperBound,
                               requestsMade, allowedQueries, tweets, verbose)
            elif verbose == "1":
                    print "Query failed for:", lowerBound, "to", upperBound
    elif verbose == "1":
            print "Query failed: Ran out of requests."
            

def findIn(myStr, myList):
    """Finds an element in a list containing a specific substring

    myStr: the substring to looked for
    myList: the list to be searched in

    return: the string containing that substring or a null string"""

    string = ''

    for s in myList:
        if myStr in s:
                string = s
                break

    return string

def parseCommands():
    """Grabs all necessary commandline arguments and returns them"""

    oathInfo=sys.argv[1]
    query=sys.argv[2]

    output=sys.argv[3]
    output = OUTPUT_NAME + output

    verbose=sys.argv[4]

    return oathInfo, query, output, verbose

"""-----------------BEGIN PROGRAM--------------------"""

commands = parseCommands()
OAuthInfo = list()
f=open(str(commands[OATH]))
inputFile=f.readlines()

#Processing of OAuth codes

if commands[VERBOSE] == "1":
    print "Grabbing oathInformation from:", commands[OATH]

for i in range(4):

      line =inputFile[i]

      if line != "\n":
              if i == 0:
                      line = line.replace("Consumer Key:", "")
              elif i == 1:
                      line = line.replace("Consumer Secret:", "")
              elif i == 2:
                      line = line.replace("Access Token:", "")
              elif i == 3:
                      line = line.replace("Access Secret:", "")

              line = line.replace('\n', "")
              line = line.replace(' ', "")
              
              OAuthInfo.append(line)

#Initializes the user
api = twitter.Api(consumer_key=OAuthInfo[0],
                  consumer_secret=OAuthInfo[1],
                  access_token_key=OAuthInfo[2],
                  access_token_secret=OAuthInfo[3])

#Initializes the query in prep for grabbing tweets
query = commands[QUERY]

if commands[VERBOSE] == '1':
    print 'Query:', query

statuses = list()

statuses = api.GetSearch(query, count=1, lang='en')

if len(statuses) != 0:
        approxBound = statuses[0].id
        
        lowerBound = 0
        upperBound = approxBound // 2
        allowedQueries = (maxRequests // 2) - 1

        Intervals = list()
        requestsMade = list()
        requestsMade.append(0)
        statuses = list()
        
        #Grabs tweets from first half of interval
        grabTweets(api, query, Intervals, lowerBound, upperBound, 
                   requestsMade, allowedQueries, statuses, commands[VERBOSE])

        if commands[VERBOSE] == "1":
            print "Stats after initial", requestsMade, "grabs:"
            print "    Approx Bound:", approxBound
            print "    Lower Bound Start:", lowerBound
            print "    Upper Bound Start:", upperBound
            print "    Requests made:", requestsMade[0]
            print "    New allowed queries:", allowedQueries + (maxRequests // 2 - requestsMade[0])
        
        allowedQueries = allowedQueries + (maxRequests // 2 - requestsMade[0]) 

        requestsMade[0] = 0
        
        #Grabs tweets from second half of interval
        grabTweets(api, query, Intervals, upperBound, approxBound, 
                   requestsMade, allowedQueries, statuses, commands[VERBOSE])

        if commands[VERBOSE] == "1":
            print "Stats after latter", requestsMade, "grabs:"
            print "    Lower Bound start:", lowerBound
            print "    Upper Bound start:", upperBound
            print "    Requests made:", requestsMade[0]
            print "Total tweets after both grabs:", len(statuses)
            print "Outputting raw data to:", commands[OUTPUT]

        output = open(str(commands[OUTPUT]), 'w')
        
        output.write(str(len(statuses)))
        output.write('\n\n')

        for s in statuses:
                 output.write(s.user.screen_name.encode("UTF-8"))
                 output.write('\n')
                
                 obj = s.GetPlace()

                 if obj is not None:
                         output.write(obj["full_name"].encode("UTF-8"))
                         output.write('\n')
                         
                         if obj['bounding_box']['coordinates'] is not None:
                            output.write("YES")
                            output.write("\n")
                            fixed = str(obj['bounding_box']['coordinates'])
                            fixed = fixed.replace("[[[", "[[")
                            fixed = fixed.replace("]]]", "]]")
                            output.write(str(fixed))
                            output.write('\n')
                         else:
                            output.write("NONE,")
                            output.write('\n')
                 else:
                         output.write("NONE,")
                         output.write('\n')

                 s.text = "\"\"" + s.text + "\"\""
                 s.text = s.text.replace("\n", " ")
                 output.write(s.text.encode("UTF-8"))

                 output.write('\n\n')
        
        output.close()

        if commands[VERBOSE] == "1":
            print "Finished grabbing raw data."
