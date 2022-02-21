#ifndef MODEL_METADATA_H
#define MODEL_METADATA_H

struct metadata
{
    char const *name;
    char const *acc;
};

static inline struct metadata metadata(char const *name, char const *acc)
{
    return (struct metadata){name, acc};
}

#endif
