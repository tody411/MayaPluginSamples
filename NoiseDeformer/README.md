
NoiseDeformer
====

Simple noise node (deformer plug-in).

## Result

This command can add noise to the selected mesh.

| ![Original] (results/original.png) | ![Noise2] (results/noise_deformer.2.png) | ![Noise3] (results/noise_deformer.3.png) |
|-------------------------|-----------------|-----------------|
| Original mesh   | Noise mesh with $\sigma=0.005$  | Noise mesh with $\sigma=0.01$  |

## Usage

1. Select the target mesh.
2. Run the following command.

###MEL:
``` bash
deformer -type NoiseDeformer;
```
###Python:
``` python
cmds.deformer( type="NoiseDeformer" );
```

|Parameter|Description |
|----------|------------|
|sigma     |Noise parameter |

## Examples

###MEL:
``` bash
polyTorus -sx 40 -sy 40 -r 5.0 -sr 2.0;
deformer -type NoiseDeformer;
```

###Python:
``` python
cmds.polyTorus(sx=40, sy=40, r=5.0, sr=2.0)
cmds.deformer( type="NoiseDeformer" );
```

## License

The MIT License 2015 (c) tody