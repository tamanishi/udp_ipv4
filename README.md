# Learning socket programming

## send recv

``` sh
cc send.c -o send
cc recv.c -o recv

./recv

# in other terminal
./send
```

## echo

``` sh
cc send-recv.c -o send-recv
cc echo.c -o echo

./echo

# in other terminal
./send-recv
```
