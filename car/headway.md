There are three modes during which a rear end collision can occur with a sudden stop of the leading vehicle.  At time `t=0`, the leader beings braking for whatever reason.  The first phase is a until the follower reacts and hits its brakes, `t_r`.  At time `t=t_r`, phase two begins and now both vehicles are slowing down, but the follower may still be going too fast.  When the leader finally stops, `t=t_{stop}^l`, phase three begins as the follower continues.  If the follower stops here without a collision, phase three ends and all is safe.

To ensure safety, we must be sure that tour actual headway is greater than the initial crashing headway across these phases.  That is, find the maximum initial headway that just barely results in a crash and make our safe following headway more than that.  The easy way to get the max is to ocmpute `h_{init}` at each transition time as well as the time of the max headway within each phase.  This is nominally seven points, including `h_{init} = 0` at `t=0` as the first point.

To find the time of max headway within a phase, we solve `dh_{init}/dt = 0` for `t`.  First, verify that `t_{max}^i` (the time at which the max occurs within phase `i`) is within the actual time bounds for that phase (see Table \ref{tab:headway}).  Now, this could also be a minimum headway.  But, it's more effort to determine that than to simply compute the headway and compare.  As all the phases are quadratic in time, they have one global max or min, so we need not worry about multiple solutions.  So, find the right times for the right phases, compute all the headways (including at phase transitions), and take the longest to avoid all rear-end collisions from sudden stops.

| Phase                    |   Start `t`       | End `t`        | `h_init` for crash    |   Diagram          |
| ------------------------ | ----------------- | -------------- | --------------------- | ------------------ |
| 0 -> 1                   | -                 | 0              | 0                     |                    |
| 1                        | 0                 | `t_r`          | ![phase1]             | \input{diag1.tex}  |
| 1 -> 2                   | -                 | `t_r`          | ![phase12]            |                    |
| 2                        | `t_r`             | `t_{stop}^l`   | ![phase2]             | \input{diag2.tex}  |
| 2 -> 3                   | -                 | `t_{stop}^l`   | ![phase23]            |                    |
| 3                        | `t_{stop}^l`      | `t_{stop}^f`   | ![phase3]             | \input{diag3.tex}  |
| 3 -> Fin                 | -                 | `t_{stop}^f`   | ![phase3fin]          |                    |

![Phase 1][phase1]
![Phase 1 to 2][phase12]
![Phase 2][phase2]
![Phase 2 to 3][phase23]
![Phase 3][phase3]
![Phase 3 to Finish][phase3fin]

[phase1]: http://latex.codecogs.com/gif.latex?-%5Cfrac%7B%28v_l%20-%20v_f%29%5E2%7D%7B2%20%28a_f%20-%20d_l%29%7D
<!-- \frac{a+b}{a-b^2} -->

[phase12]: http://latex.codecogs.com/gif.latex?%5Cfrac%7B1%7D%7B2%7D%20%5C%2C%20%7B%5Cleft%28a_f%20-%20d_l%5Cright%29%7D%20t_r%5E%7B2%7D%20&plus;%20t_r%20%28%20v_1%20-%20v_0%29
<!-- \frac{1}{2} \, {\left(a_f - d_l\right)} t_r^{2} + t_r ( v_1 - v_0) -->

[phase2]: http://latex.codecogs.com/gif.latex?%5Cfrac%7B%7B%5Cleft%28a_f%5E%7B2%7D%20-%20a_f%20d_l%20-%20%7B%5Cleft%28a_f%20-%20d_l%5Cright%29%7D%20d_f%5Cright%29%7D%20t_r%5E%7B2%7D%20-%202%20%5C%2C%20%7B%5Cleft%28a_f%20-%20d_f%5Cright%29%7D%20t_r%20v_l%20&plus;%20v_l%5E%7B2%7D%20&plus;%202%20%5C%2C%20%7B%5Cleft%28%7B%5Cleft%28a_f%20-%20d_f%5Cright%29%7D%20t_r%20-%20v_l%5Cright%29%7D%20v_f%20&plus;%20v_f%5E%7B2%7D%7D%7B2%20%5C%2C%20%7B%5Cleft%28d_l%20-%20d_f%5Cright%29%7D%7D
<!-- \frac{{\left(a_f^{2} - a_f d_l - {\left(a_f - d_l\right)} d_f\right)} t_r^{2} - 2 \, {\left(a_f - d_f\right)} t_r v_l + v_l^{2} + 2 \, {\left({\left(a_f - d_f\right)} t_r - v_l\right)} v_f + v_f^{2}}{2 \, {\left(d_l - d_f\right)}} -->

[phase23]: http://latex.codecogs.com/gif.latex?%5Cfrac%7B1%7D%7B2%7D%20%5C%2C%20d_f%20%7B%5Cleft%28t_r%20-%20%5Cfrac%7Bv_l%7D%7Bd_l%7D%5Cright%29%7D%5E%7B2%7D%20&plus;%20%5Cfrac%7B1%7D%7B2%7D%20%5C%2C%20a_f%20t_r%5E%7B2%7D%20-%20%7B%5Cleft%28a_f%20t_r%20&plus;%20v_f%5Cright%29%7D%20%7B%5Cleft%28t_r%20-%20%5Cfrac%7Bv_l%7D%7Bd_l%7D%5Cright%29%7D%20&plus;%20t_r%20v_f%20-%20%5Cfrac%7B3%20%5C%2C%20v_l%5E%7B2%7D%7D%7B2%20%5C%2C%20d_l%7D
<!-- \frac{1}{2} \, d_f {\left(t_r - \frac{v_l}{d_l}\right)}^{2} + \frac{1}{2} \, a_f t_r^{2} - {\left(a_f t_r + v_f\right)} {\left(t_r - \frac{v_l}{d_l}\right)} + t_r v_f - \frac{3 \, v_l^{2}}{2     \, d_l} -->

[phase3]: http://latex.codecogs.com/gif.latex?-%5Cfrac%7B%7B%5Cleft%28a_f%5E%7B2%7D%20d_l%20-%20a_f%20d_l%20d_f%5Cright%29%7D%20t_r%5E%7B2%7D%20&plus;%203%20%5C%2C%20d_f%20v_l%5E%7B2%7D%20&plus;%202%20%5C%2C%20%7B%5Cleft%28a_f%20d_l%20-%20d_l%20d_f%5Cright%29%7D%20t_r%20v_f%20&plus;%20d_l%20v_f%5E%7B2%7D%7D%7B2%20%5C%2C%20d_l%20d_f%7D
<!-- -\frac{{\left(a_f^{2} d_l - a_f d_l d_f\right)} t_r^{2} + 3 \, d_f v_l^{2} + 2 \, {\left(a_f d_l - d_l d_f\right)} t_r v_f + d_l v_f^{2}}{2 \, d_l d_f} -->


[phase3fin]: http://latex.codecogs.com/gif.latex?-%5Cfrac%7B%7B%5Cleft%28a_f%5E%7B2%7D%20d_l%20-%20a_f%20d_l%20d_f%5Cright%29%7D%20t_r%5E%7B2%7D%20&plus;%203%20%5C%2C%20d_f%20v_l%5E%7B2%7D%20&plus;%202%20%5C%2C%20%7B%5Cleft%28a_f%20d_l%20-%20d_l%20d_f%5Cright%29%7D%20t_r%20v_f%20&plus;%20d_l%20v_f%5E%7B2%7D%7D%7B2%20%5C%2C%20d_l%20d_f%7D
<!-- -\frac{{\left(a_f^{2} d_l - a_f d_l d_f\right)} t_r^{2} + 3 \, d_f v_l^{2} + 2 \, {\left(a_f d_l - d_l d_f\right)} t_r v_f + d_l v_f^{2}}{2 \, d_l d_f} -->
