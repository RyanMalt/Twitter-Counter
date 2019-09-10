---------------------------------README.TXT-------------------------------------

Dev: Ryan Malthaner
Version: 1.0
Date: 5/1/2015
Program: Tweetalyzer

Credit:
    In Python Modules the code from python-twitter-1.1, httplib2-master,
        python-oath2-master, simplejson-3.6.5, and setuptools-15.2 comes from
        various authors.
    
    python-twitter-1.1:     The Python-Twitter Developers (c) 2013
    httplib2-master:        Joe Gregorio (c) 2006
    python-oath2-master:    Leah Culver (c) 2007
    simplejson-3.6.5:       Bob Ippolito (c) 2006
    setuptools-15.2:        Python Packaging Authority
        
    Much thanks to each one of these people and/or groups.  Without their code,
        there would have been even more blood, sweat, and tears poured into this
        project.
 
--------------------------------------------------------------------------------

----------------------------------SUMMARY---------------------------------------

Purpose:
    Created to analyze the word frequency of tweets associated with a particular
        hashtag.

Oauth authorization:
    In order for this program to work, a series of "passwords" are needed from
        the online twitter api.  This requires the registering of a twitter app
        and the generating of these tokens and secret keys.
    
    Once these four keys have been obtained, place them into the oauth.txt or
        whatever file you like as long as it obeys the formatting of the
        oauth.txt file setup.

Installation:
    Theoretically, you should just be able to run install.sh, and it should be
        okay.  Granted, I haven't tested this at all, but my theory is pretty
        good.
        
    If install.sh fails, manually building and install everything in
        PythonModules will be necessary.
        ex)
            #cd httplib2-master
            #python setup.py build
            #sudo python setup.py install
        
        -Make sure to install setuptools-15.2 first, then httplib2-master,
            python-oauth2-master, and simplejson-3.6.5, then finally,
            python-twitter-1.1
        
    After installing all the python dependencies, compile all the .cpp's in 
        Source_Code, name the program "Tweetalyzer.out," then move it into the
        main Twitter_Project directory
    
    Finally, you likely will have to chmod +x analyzeTwitter.sh, Tweetalyzer.out
        and twitterScript.py.
    
    Now, feel free to play with your new toy!

Commandline arguments:
     -a [OATH FILE]:
        -This option tells the user where the Oauthorization file information is
        -The file chosen must be of a very specific format as given by:
        ex)
            Consumer Key: YOURKEYHERE
            Consumer Secret: YOURSECRETHERE
            Access Token: YOURTOKENHERE
            Access Secret: YOURSECRETHERE
        
        -All spacing and words before the actual keys MUST be there, or the
            program WILL break
        -The default file for this is "oauth.txt".
    
     -h:
        -This option prints out the possible options and their usage
        ex)
            Options: -a [OATH FILE] -o [OUTPUT] -t [RAW_OUTPUT] -q [QUERY] -v -h
        
     -o [OUTPUT]:
        -This option allows the user to say where the final processed output of 
            the program should go (see Return)
        -If this option is not given, the default parameter is "output.txt"
        ex)
            -o finishedProduct.txt
     
     -q [QUERY]:
        -This option gives the program the query that it will use to poll the
            twitter API with.
        -This option MUST be present or the program will not run.
        ex)
            -q \#ryansproject
        
        -Notice that if querying for a particular hashtag, being the hashtag 
            with the escape character.  Otherwise, bash just ignores it and
            the program will crash.
      
      -t [RAW_OUTPUT]:
        -This option tells the program where to send the raw grabbed and
            formatted tweets.
        ex)
            -t tweets.txt
        
        -Notice that "raw_" will be added to this to distinguish it from final
            output.
      
      -v:
        -This option allows for verbose mode.  I recommend this option to be
            used at all times if not being used with a script.  It is much
            better for seeing progress
        ex)
            -v
        
        -Notice that some messages will persist regardless.  This is largely
            due to several very late nights and an unwillingness to rewrite 
            large swathes.  Perhaps in a future update. 
            
Return:
    Creates a file filled with
        -list of unique words and their frequencies
        -list of all people mentioned in the tweets
        -list of all unique hashtags used in the tweets
        -list of all locations associated with the tweets
        -brief summary of these statistics at the very bottom of the file


