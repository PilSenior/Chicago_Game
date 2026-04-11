#!/bin/bash
echo "=== SCENARIO 5 TEST: Hit→Miss→Hit (should return 0) ==="
echo ""
printf "1\nY\nY\nN\n" | ./chicago 2>&1 | grep -A 20 "Round 1"
