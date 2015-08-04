
LaplacianSmoother
====

Laplacian smoothing node (deformer plug-in).

## Result

This node can smooth the selected mesh.

| ![LaplacianSmoother1] (results/laplacian_smoother.1.png) | ![LaplacianSmoother2] (results/laplacian_smoother.2.png) | ![LaplacianSmoother3] (results/laplacian_smoother.3.png) |![LaplacianSmoother4] (results/laplacian_smoother.4.png) |
|-------------------------|-----------------|-----------------|----------------|
| Original mesh   | Noise mesh with sigma=0.03  | Smooth mesh with lambda=0.05  |Smooth mesh with lambda=0.5  |

## Usage

1. Select the target mesh.
2. Run the following command.

###MEL:
``` bash
deformer -type LaplacianSmoother;
```
###Python:
``` python
cmds.deformer( type="LaplacianSmoother" );
```

|Parameter|Description |
|----------|------------|
|lambda     |Smoothing parameter |

## Examples

###MEL:
``` bash
polyTorus -sx 40 -sy 40 -r 5.0 -sr 2.0;
deformer -type NoiseDeformer;
deformer -type LaplacianSmoother;
```

###Python:
``` python
cmds.polyTorus(sx=40, sy=40, r=5.0, sr=2.0)
cmds.deformer( type="NoiseDeformer" );
cmds.deformer( type="LaplacianSmoother" );
```

## License

The MIT License 2015 (c) tody