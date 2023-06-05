### All contributions, bug reports, bug fixes, documentation improvements, enhancements, and ideas are welcome.
-----------------------------------------------------------------------------------------------------------------
##### Sunday -- 04-06-2023
We change color sensor pins to be:
<ul>
  <li> Color Sensor Front to Back. </li>
  <li> Color Sensor Back to Front. </li>
</ul>

So...
In Code line 8 and 9:

```
// const int clrF=8,clrB=2; // We comment it because the clf yellow wire signal not work
const int clrF = 2, clrB = 8;
```

From Pins.txt file we gonna like this but we do not change anything in Pins.txt file.
But in actual code we will change it.

This Update gonna be after problem in Sumo Competition (Sunday 04-06-2023)

The Color Sensor Front not work, we thing the problem because damage from the 
Signal yellow wire. 
