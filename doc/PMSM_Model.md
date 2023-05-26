# PMSM Model

## Before Reading Further
Due to the github page latex rendering issue, the latex formular are replaced with the generated svg files. The [online tool](https://editor.codecogs.com) can be used to convert latex context to svg file. Also, please reserve the orignal latex formular as comment for the purpose of version control. 

In consequence, the generated svg file can only have one (here the black is chosen) front color. For easier reading, please set the background color or the webpage or editor to white for better contrast.

## Electrical Model
This section is only for clarifying which model is used in the playground, with the method been used to solve the ordinary differential equation(ODE). For detailed explanation of how the model is created, please refer to other literatures. A very good reference could be [Electric Motor Control(Chapter 4)](https://www.sciencedirect.com/science/article/abs/pii/B9780128121382000040).

### Simplified Model (Expressed in d-q phase)
A simplified model of interior PMSM(IPMSM) is described [here](https://www.mathworks.com/help/autoblks/ref/interiorpmsm.html).

Reform the electrical model of the equations into a state space representation, we can get:
<!-- $$
\frac{d}{dt} 
\begin{bmatrix} 
i_{d}\\[0.3em]
i_{q}
\end{bmatrix}
= 
\begin{bmatrix}
-\frac{R}{L_{d}} & \frac{L_{q}}{L_{d}}p\omega_{m} \\[0.3em]
-\frac{L_{d}}{L_{q}}p\omega_{m} & -\frac{R}{L_{q}}
\end{bmatrix}
\begin{bmatrix} 
i_{d}\\[0.3em]
i_{q}
\end{bmatrix}
+
\begin{bmatrix}
\frac{1}{L_{d}} & 0 \\[0.3em]
0 & \frac{1}{L_{q}}
\end{bmatrix}
\begin{bmatrix} 
u_{d}\\[0.3em]
u_{q}
\end{bmatrix}
+
\begin{bmatrix} 
0\\[0.3em]
-1
\end{bmatrix}
\frac{\lambda_{pm}p\omega_{m}}{L_{d}}
$$ -->
![image](.pictures/simplified_pmsm_model.svg)

For a surfaced mounted PMSM (SPMSM), simply set $L_{d} = L_{q} = L_{s}$ in the equation, where $L_{s}$ is the motor phase inductance.
### Original Model (Expressed in motor a-b-c phase)

As is described in the [Matlab Webpage](https://www.mathworks.com/help/sps/ref/pmsm.html), the PMSM electrical system can be stated as: 
<!-- $$
\begin{bmatrix}
u_{a}\\[0.3em]
u_{b}\\[0.3em]
u_{c}
\end{bmatrix}
=
R_{s}\bold{I}
\begin{bmatrix}
i_{a}\\[0.3em]
i_{b}\\[0.3em]
i_{c}
\end{bmatrix}
+
\frac{d}{dt}
\begin{bmatrix}
\phi_{a}\\[0.3em]
\phi_{b}\\[0.3em]
\phi_{c}
\end{bmatrix}
$$ -->
![image](.pictures/pmsm_current_model.svg)  
Where
<!-- $$
\begin{bmatrix}
\phi_{a}\\[0.3em]
\phi_{b}\\[0.3em]
\phi_{c}
\end{bmatrix}
=
\bold{L}
\begin{bmatrix}
i_{a}\\[0.3em]
i_{b}\\[0.3em]
i_{c}
\end{bmatrix}
+
\begin{bmatrix}
\phi_{am}\\[0.3em]
\phi_{bm}\\[0.3em]
\phi_{cm}
\end{bmatrix}
$$ -->
![image](.pictures/pmsm_flux_model.svg)    
The $I_{3 \times 3}$ is the identity matrix and $L_{3 \times 3}$ is the inductance matrix, whose elements are position dependent, which can be calculated as described in the [Matlab Webpage for pmsm model](https://www.mathworks.com/help/sps/ref/pmsm.html). Sorting the above two equations, we can get the electrical model in the state-space description:
<!-- $$
\frac{d}{dt}
\begin{bmatrix}
i_{a}\\[0.3em]
i_{b}\\[0.3em]
i_{c}
\end{bmatrix}
=
-\bold{L}^{-1}(R_{s}\bold{I}+\frac{d}{dt}\bold{L})
\begin{bmatrix}
i_{a}\\[0.3em]
i_{b}\\[0.3em]
i_{c}
\end{bmatrix}
+
\bold{L}^{-1}
\begin{bmatrix}
u_{a}\\[0.3em]
u_{b}\\[0.3em]
u_{c}
\end{bmatrix}
-
\bold{L}^{-1}\frac{d}{dt}
\begin{bmatrix}
\phi_{am}\\[0.3em]
\phi_{bm}\\[0.3em]
\phi_{cm}
\end{bmatrix}
$$ -->
![image](.pictures/original_pmsm_model.svg)   

### Solve the ODE
Both simplified and original electrical model can be expressed as:
<!-- $$
\dot{x}_{n\times 1} = \bold{A}_{n\times n}x_{n\times 1} + \bold{B}_{n\times n}u_{n\times 1} + w_{n\times 1}
$$ -->
![image](.pictures/pmsm_model_ss.svg)   
The above equation is a time-invariate linear ordinary differential equation, where $n=2$ for simplified model and $n=3$ for original model. It is worthy noting that in original model, the Matrix $A$, $B$ and vector $w$ are position and velocity dependent, which makes them also time dependent. However, in compared to the electrical states $i$ and $u$, the bandwith of position and velocity is very low. As a result, we can treat them as constant martix when solving the equation for the current.

#### Analytical Solution
（tbd）

#### Numerical Solution
Apply [bilinear transformation](https://en.wikipedia.org/wiki/Bilinear_transform) to $\dot{x}$ and assume the sample time is $t_{s}$, we can get:
<!-- $$
\frac{2}{t_{s}}\frac{z-1}{z+1}x = \bold{A}x + \bold{B}u + w
$$ -->
![image](.pictures/pmsm_model_ss_bilinear.svg)   
Which then can be extracted to:
<!-- $$
(\bold{I}-\frac{1}{2}t_{s}\bold{A})x_{k+1} = (\bold{I}+\frac{1}{2}t_{s}\bold{A})x_{k} + \frac{1}{2}t_{s}\bold{B}(u_{k+1}+u_{k}) + t_{s}w_{k}
$$ -->
![image](.pictures/pmsm_model_discrete_full.svg)   
Thus, the state $x_{k+1}$ can be calculated as:
<!-- $$
x_{k+1} = \bold{\tilde A}x_{k} + \bold{\tilde B}(u_{k+1}+u_{k}) + \bold{\tilde w}
$$ -->
![image](.pictures/pmsm_model_discrete_short.svg)   
Where
<!-- $$
\bold{\tilde A} = (\bold{I}-\frac{1}{2}t_{s}\bold{A})^{-1}(\bold{I}+\frac{1}{2}t_{s}\bold{A})
$$ -->
![image](.pictures/pmsm_model_discrete_a.svg)   
<!-- $$
\bold{\tilde B} = \frac{1}{2}t_{s}(\bold{I}-\frac{1}{2}t_{s}\bold{A})^{-1}\bold{B}
$$ -->
![image](.pictures/pmsm_model_discrete_b.svg) 
<!-- $$
\bold{\tilde w} = t_{s}(\bold{I}-\frac{1}{2}t_{s}\bold{A})^{-1}w_{k}
$$ -->
![image](.pictures/pmsm_model_discrete_w.svg) 
## Dynamic Model
